#include <Arduino.h>

#include "slmp_config.h"
#include "radiolib_transport.h"
#include "slmp_display.h"
#include "slmp_packet.h"

RadioLibTransport transport;
SlmpDisplay screen;

String inputMessage;

uint8_t receiveBuffer[SLMP_MAX_PACKET_SIZE];

void testSlmpPacket() {

    SLMP::PacketHeader original = {
        SLMP::VERSION,
        static_cast<uint8_t>(SLMP::PacketType::DATA),
        0x0001,
        0x0002,
        0x12345678,
        1,
        0x00,
        5
    };

    uint8_t buffer[SLMP::HEADER_SIZE];

    bool encoded = SLMP::serializeHeader(
        original,
        buffer,
        sizeof(buffer)
    );

    if (!encoded) {
        Serial.println("Serialization FAILED");
        return;
    }

    Serial.println("Serialized packet:");

    for (size_t i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] < 0x10) Serial.print("0");

        Serial.print(buffer[i], HEX);
        Serial.print(" ");
    }

    Serial.println();

    SLMP::PacketHeader decoded;

    bool valid = SLMP::deserializeHeader(
        buffer,
        sizeof(buffer),
        decoded
    );

    if (!valid) {
        Serial.println("Deserialization FAILED");
        return;
    }

    Serial.println("Deserialization SUCCESS");

    Serial.printf(
        "Source: 0x%04X\n",
        decoded.sourceId
    );

    Serial.printf(
        "Destination: 0x%04X\n",
        decoded.destinationId
    );
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    screen.begin();
    screen.showBoot(SLMP_DEVICE_ID);

    Serial.println();
    Serial.println("SecureLoRa raw radio test");
    // Test du protocole SLMP
    Serial.println("\n=== SLMP PACKET TEST ===");
    testSlmpPacket();
    Serial.println("========================\n");


    Serial.printf(
        "Device ID: 0x%04X\n",
        SLMP_DEVICE_ID
    );

    if (!transport.begin()) {
        Serial.println("Radio initialization failed.");

        screen.showRadioError(-2);

        while (true) {
            delay(1000);
        }
    }

    Serial.println("Radio ready.");

    screen.showRadioReady(SLMP_DEVICE_ID);

    Serial.println("Type a message and press Enter.");
}

void loop() {

    while (Serial.available()) {
        char c = Serial.read();

        if (c == '\r') {
            continue;
        }

        if (c == '\n') {
            if (inputMessage.length() > 0) {
                bool success = transport.send(
                    reinterpret_cast<const uint8_t*>(
                        inputMessage.c_str()
                    ),
                    inputMessage.length()
                );

                Serial.println(
                    success ? "Message sent." : "Send failed."
                );

                inputMessage = "";
            }
        } else if (inputMessage.length() < 200) {
            inputMessage += c;
        }
    }

    int receivedLength = transport.receive(
        receiveBuffer,
        sizeof(receiveBuffer)
    );

    if (receivedLength > 0) {
        String message;

        for (int i = 0; i < receivedLength; i++) {
            message += static_cast<char>(receiveBuffer[i]);
        }

        Serial.print("Received: ");
        Serial.println(message);

        screen.showMessage(message);
    }

    delay(10);
}

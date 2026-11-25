#include "radiolib_transport.h"

RadioLibTransport::RadioLibTransport()
    : spiSettings(2000000, MSBFIRST, SPI_MODE0),

      module(new Module(
          PIN_LORA_NSS,
          PIN_LORA_DIO0,
          PIN_LORA_RST,
          PIN_LORA_DIO1,
          SPI,
          spiSettings
      )),

      radio(new SX1276(module)) {
}


bool RadioLibTransport::begin() {

    Serial.println("Initializing LoRa SPI...");

    // Initialisation SPI personnalisée
    SPI.begin(
        PIN_LORA_SCK,
        PIN_LORA_MISO,
        PIN_LORA_MOSI,
        PIN_LORA_NSS
    );

    Serial.println("Initializing SX1276...");

    ConfigLoRa_t config;

    config.frequency = static_cast<uint32_t>(
        SLMP_RF_FREQUENCY_MHZ * 1000000.0
    );

    config.bandwidth = SLMP_LORA_BANDWIDTH;
    config.spreadingFactor = SLMP_LORA_SF;
    config.codingRate = SLMP_LORA_CR;
    config.power = SLMP_LORA_POWER;
    config.preambleLength = SLMP_LORA_PREAMBLE;

    int16_t state = radio->begin(config);

    if (state != RADIOLIB_ERR_NONE) {

        Serial.print("LoRa initialization failed: ");
        Serial.println(state);

        ready = false;

        return false;
    }

    ready = true;

    Serial.println("LoRa initialized successfully");

    return true;
}


bool RadioLibTransport::send(
    const uint8_t* data,
    size_t length
) {

    if (!ready || data == nullptr || length == 0) {
        return false;
    }

    if (length > SLMP_MAX_PACKET_SIZE) {
        Serial.println("Packet too large");
        return false;
    }

    int16_t state = radio->transmit(
        const_cast<uint8_t*>(data),
        length
    );

    if (state != RADIOLIB_ERR_NONE) {

        Serial.print("TX error: ");
        Serial.println(state);

        return false;
    }

    Serial.println("Packet transmitted");

    radio->startReceive();

    return true;
}


int RadioLibTransport::receive(
    uint8_t* buffer,
    size_t capacity
) {

    if (!ready || buffer == nullptr || capacity == 0) {
        return 0;
    }

    size_t packetLength = radio->getPacketLength();

    if (packetLength == 0) {
        return 0;
    }

    if (packetLength > capacity) {

        Serial.println("Received packet exceeds buffer");

        radio->startReceive();

        return -1;
    }

    int16_t state = radio->readData(
        buffer,
        packetLength
    );

    radio->startReceive();

    if (state != RADIOLIB_ERR_NONE) {

        Serial.print("RX error: ");
        Serial.println(state);

        return -1;
    }

    return static_cast<int>(packetLength);
}
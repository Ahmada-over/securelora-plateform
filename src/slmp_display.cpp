#include "slmp_display.h"

void SlmpDisplay::begin() {
    oled.init();
    oled.flipScreenVertically();
    oled.setFont(ArialMT_Plain_10);

    oled.clear();
    oled.drawString(0, 20, "SecureLoRa");
    oled.drawString(0, 36, "Starting...");
    oled.display();
}

void SlmpDisplay::drawHeader() {
    oled.setFont(ArialMT_Plain_10);
    oled.drawString(0, 0, "SECURELORA");
    oled.drawHorizontalLine(0, 12, 128);
}

void SlmpDisplay::showBoot(uint16_t deviceId) {
    oled.clear();
    drawHeader();

    oled.drawString(0, 19, "Device:");
    oled.drawString(45, 19, String("0x") + String(deviceId, HEX));

    oled.drawString(0, 35, "Initializing radio...");
    oled.display();
}

void SlmpDisplay::showRadioReady(uint16_t deviceId) {
    oled.clear();
    drawHeader();

    oled.drawString(0, 17, "DEVICE");

    oled.drawString(
        45, 17,
        String("0x") + String(deviceId, HEX)
    );

    oled.drawString(0, 32, "LoRa: READY");
    oled.drawString(0, 46, "Waiting for data...");

    oled.display();
}

void SlmpDisplay::showRadioError(int error) {
    oled.clear();
    drawHeader();

    oled.drawString(0, 20, "RADIO ERROR");

    oled.drawString(
        0, 38,
        String("Code: ") + String(error)
    );

    oled.display();
}

void SlmpDisplay::showMessage(const String& message) {
    oled.clear();
    drawHeader();

    oled.drawString(0, 17, "MESSAGE RECEIVED");

    oled.drawStringMaxWidth(0, 32, 128, message);

    oled.display();
}
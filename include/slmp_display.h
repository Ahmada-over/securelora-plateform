#pragma once

#include <Arduino.h>
#include <SSD1306Wire.h>

class SlmpDisplay {
public:
    void begin();
    void showBoot(uint16_t deviceId);
    void showRadioReady(uint16_t deviceId);
    void showRadioError(int error);
    void showMessage(const String& message);

private:
    SSD1306Wire oled = SSD1306Wire(0x3C, 21, 22);

    void drawHeader();
};
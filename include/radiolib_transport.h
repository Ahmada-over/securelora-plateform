#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

#include "slmp_transport.h"
#include "slmp_config.h"

class RadioLibTransport final : public SlmpTransport {

public:

    RadioLibTransport();

    bool begin() override;

    bool send(
        const uint8_t* data,
        size_t length
    ) override;

    int receive(
        uint8_t* buffer,
        size_t capacity
    ) override;

private:

    SPISettings spiSettings;

    Module* module;
    SX1276* radio;

    bool ready = false;
};
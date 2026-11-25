#pragma once
#include <Arduino.h>
static constexpr int8_t PIN_LORA_SCK=5, PIN_LORA_MISO=19, PIN_LORA_MOSI=27;
static constexpr int8_t PIN_LORA_NSS=18, PIN_LORA_DIO0=26, PIN_LORA_RST=23, PIN_LORA_DIO1=33;
#ifndef SLMP_DEVICE_ID
#define SLMP_DEVICE_ID 0x0001
#endif
#ifndef SLMP_RF_FREQUENCY_MHZ
#error "Define the RF frequency only after verifying hardware and local regulations."
#endif
static constexpr size_t MAX_TEST_TEXT=180;

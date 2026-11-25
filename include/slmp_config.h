#pragma once

#include <Arduino.h>

// Identité du terminal
#define SLMP_DEVICE_ID 0x0001

// Fréquence provisoire : à confirmer avant toute émission
#define SLMP_RF_FREQUENCY_MHZ 868.0

// Broches LoRa — LILYGO T3 V1.6.1
#define PIN_LORA_SCK   5
#define PIN_LORA_MISO  19
#define PIN_LORA_MOSI  27

#define PIN_LORA_NSS   18
#define PIN_LORA_RST   23
#define PIN_LORA_DIO0  26
#define PIN_LORA_DIO1  33

// Paramètres LoRa
#define SLMP_LORA_BANDWIDTH 125000
#define SLMP_LORA_SF        9
#define SLMP_LORA_CR        7
#define SLMP_LORA_POWER     10
#define SLMP_LORA_PREAMBLE  8

#define SLMP_MAX_PACKET_SIZE 255
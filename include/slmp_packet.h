
#pragma once

#include <Arduino.h>

namespace SLMP {

    constexpr uint8_t VERSION = 1;

    constexpr size_t HEADER_SIZE = 21;
    constexpr size_t AUTH_TAG_SIZE = 16;

    enum class PacketType : uint8_t {
        HELLO         = 0x01,
        HELLO_ACK     = 0x02,
        FINISH        = 0x03,
        SESSION_READY = 0x04,
        DATA          = 0x05,
        ACK           = 0x06,
        PING          = 0x07,
        PONG          = 0x08,
        CLOSE         = 0x09,
        ERROR         = 0x0A
    };

    struct PacketHeader {
        uint8_t version;
        uint8_t type;
        uint16_t sourceId;
        uint16_t destinationId;
        uint32_t sessionId;
        uint64_t sequence;
        uint8_t flags;
        uint16_t payloadLength;
    };

    // Sérialisation de l'en-tête en Big Endian
    bool serializeHeader(
        const PacketHeader& header,
        uint8_t* output,
        size_t capacity
    );

    // Reconstruction de l'en-tête depuis les octets
    bool deserializeHeader(
        const uint8_t* input,
        size_t length,
        PacketHeader& header
    );

}


#include "slmp_packet.h"

namespace SLMP {

    bool serializeHeader(
        const PacketHeader& h,
        uint8_t* output,
        size_t capacity
    ) {

        if (output == nullptr || capacity < HEADER_SIZE) {
            return false;
        }

        if (h.version != VERSION) {
            return false;
        }

        size_t i = 0;

        // Version
        output[i++] = h.version;

        // Type
        output[i++] = h.type;

        // Source ID - 2 octets
        output[i++] = (h.sourceId >> 8) & 0xFF;
        output[i++] = h.sourceId & 0xFF;

        // Destination ID - 2 octets
        output[i++] = (h.destinationId >> 8) & 0xFF;
        output[i++] = h.destinationId & 0xFF;

        // Session ID - 4 octets
        output[i++] = (h.sessionId >> 24) & 0xFF;
        output[i++] = (h.sessionId >> 16) & 0xFF;
        output[i++] = (h.sessionId >> 8) & 0xFF;
        output[i++] = h.sessionId & 0xFF;

        // Sequence - 8 octets
        for (int shift = 56; shift >= 0; shift -= 8) {
            output[i++] = (h.sequence >> shift) & 0xFF;
        }

        // Flags
        output[i++] = h.flags;

        // Payload length - 2 octets
        output[i++] = (h.payloadLength >> 8) & 0xFF;
        output[i++] = h.payloadLength & 0xFF;

        return i == HEADER_SIZE;
    }


    bool deserializeHeader(
        const uint8_t* input,
        size_t length,
        PacketHeader& h
    ) {

        if (input == nullptr || length < HEADER_SIZE) {
            return false;
        }

        size_t i = 0;

        h.version = input[i++];
        h.type = input[i++];

        if (h.version != VERSION) {
            return false;
        }

        h.sourceId =
            (static_cast<uint16_t>(input[i++]) << 8);

        h.sourceId |= input[i++];

        h.destinationId =
            (static_cast<uint16_t>(input[i++]) << 8);

        h.destinationId |= input[i++];

        h.sessionId =
            (static_cast<uint32_t>(input[i++]) << 24);

        h.sessionId |=
            (static_cast<uint32_t>(input[i++]) << 16);

        h.sessionId |=
            (static_cast<uint32_t>(input[i++]) << 8);

        h.sessionId |= input[i++];

        h.sequence = 0;

        for (int j = 0; j < 8; j++) {
            h.sequence =
                (h.sequence << 8) | input[i++];
        }

        h.flags = input[i++];

        h.payloadLength =
            (static_cast<uint16_t>(input[i++]) << 8);

        h.payloadLength |= input[i++];

        return i == HEADER_SIZE;
    }

}

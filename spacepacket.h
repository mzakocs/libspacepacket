#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SPACEPACKET_ENCODED_HEADER_SIZE 6

struct spacepacket_header {
    uint8_t version;
    bool type;
    bool secondary_header_flag;
    uint16_t apid;
    uint8_t sequence_flag;
    uint16_t packet_sequence_count;
    uint16_t packet_length;
} typedef spacepacket_header_t;

/* 
    Decodes a byte buffer into a SpacePacket header struct
    Argument encoded_buf must be at least 6 bytes large
    Returns 0 on success, -1 on error
 */
static int decode_spacepacket_header(uint8_t* encoded_buf, size_t encoded_buf_size, spacepacket_header_t *header_out) {
    // Sanity checks
    if (encoded_buf == NULL || header_out == NULL || encoded_buf_size < SPACEPACKET_ENCODED_HEADER_SIZE) {
        return -1;
    }
    // Decode header
    header_out->version = (encoded_buf[0] >> 5) & 0x07;
    header_out->type = (encoded_buf[0] >> 4) & 0x01;
    header_out->secondary_header_flag = (encoded_buf[0] >> 3) & 0x01;
    header_out->apid = ((encoded_buf[0] & 0x07) << 8) | encoded_buf[1];
    header_out->sequence_flag = (encoded_buf[2] >> 6) & 0x01;
    header_out->packet_sequence_count = ((encoded_buf[2] & 0x3F) << 8) | encoded_buf[3];
    header_out->packet_length = (encoded_buf[4] << 8) | encoded_buf[5];
    return 0;
}

/* 
    Encodes a SpacePacket header struct into a byte buffer
    Argument encoded_buf_out must be at least 6 bytes large
    Returns 0 on success, -1 on error
 */
static int encode_spacepacket_header(spacepacket_header_t *header, uint8_t* encoded_buf_out, size_t encoded_buf_out_size) {
    // Sanity checks
    if (header == NULL || encoded_buf_out == NULL || encoded_buf_out_size < SPACEPACKET_ENCODED_HEADER_SIZE) {
        return -1;
    }
    // Encode header 
    encoded_buf_out[0] = (header->version << 5) | (header->type << 4) | (header->secondary_header_flag << 3) | ((header->apid >> 8) & 0x07);
    encoded_buf_out[1] = header->apid & 0xFF;
    encoded_buf_out[2] = (header->sequence_flag << 6) | ((header->packet_sequence_count >> 8) & 0x3F);
    encoded_buf_out[3] = header->packet_sequence_count & 0xFF;
    encoded_buf_out[4] = (header->packet_length >> 8) & 0xFF;
    encoded_buf_out[5] = header->packet_length & 0xFF;
    return 0;
}

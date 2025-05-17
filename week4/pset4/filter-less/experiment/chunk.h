#include <stdint.h>


typedef struct {
    uint32_t length;
    /* CHUNK_TYPE chunk_type; */
    uint8_t type[4];
    uint8_t data[4];
    uint32_t crc;
} __attribute__((__packed__))
CHUNK;

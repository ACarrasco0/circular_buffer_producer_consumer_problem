// Cicrular Buffer

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {

    uint16_t id;
    uint64_t timestamp;
    uint8_t data;

} DATA_T;
    
typedef struct {

    uint16_t size;
    uint8_t heads;
    uint8_t tails;
    DATA_T* data;

} CIRCULAR_BUFFER_T;

CIRCULAR_BUFFER_T* cb_init(uint16_t size);
int8_t cb_push(CIRCULAR_BUFFER_T* buffer, DATA_T data);
DATA_T cb_pop(CIRCULAR_BUFFER_T* buffer);
uint8_t cb_is_empty(CIRCULAR_BUFFER_T* buffer);
uint8_t cb_is_half_full(CIRCULAR_BUFFER_T* buffer);
uint8_t cb_is_full(CIRCULAR_BUFFER_T* buffer);
void cb_clear(CIRCULAR_BUFFER_T* buffer);
void cb_deinit(CIRCULAR_BUFFER_T* buffer);
uint16_t cb_used(CIRCULAR_BUFFER_T* buffer);


#endif //CIRCULAR_BUFFER_H
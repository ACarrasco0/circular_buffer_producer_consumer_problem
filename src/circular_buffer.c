// Circular Buffer

#include "circular_buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

CIRCULAR_BUFFER_T* cb_init(uint16_t size)
{
    CIRCULAR_BUFFER_T* new_buffer = (CIRCULAR_BUFFER_T*)malloc(
        sizeof(*new_buffer) + sizeof(uint8_t) * size);
    if(!new_buffer) return NULL;

    DATA_T* allocated_data_buffer = (DATA_T*)malloc(sizeof(DATA_T) * size);
    if (allocated_data_buffer == NULL) {
        free(new_buffer);
        return NULL;
    }
    new_buffer->data = allocated_data_buffer;

    new_buffer->size  = size;
    new_buffer->heads = 0;
    new_buffer->tails = 0;

    memset(new_buffer->data, 0, sizeof(DATA_T) * size);

    return new_buffer;
}

int8_t cb_push(CIRCULAR_BUFFER_T* buffer, DATA_T new_data)
{
    if (cb_is_full(buffer)) return -1;
    *(buffer->data + buffer->heads) = new_data;
    buffer->heads = (buffer->heads + 1) % buffer->size;
    return 0;
}

DATA_T cb_pop(CIRCULAR_BUFFER_T* buffer)
{
    if (cb_is_empty(buffer)) return (DATA_T){0};
    DATA_T pop_data = *(buffer->data + buffer->tails);
    buffer->tails = (buffer->tails + 1) % buffer->size;
    return pop_data;
}

uint8_t cb_is_empty(CIRCULAR_BUFFER_T* buffer)
{
    return buffer->heads == buffer->tails;
}

uint8_t cb_is_half_full(CIRCULAR_BUFFER_T* buffer)
{
    uint16_t used;

    if (buffer->heads >= buffer->tails)
        used = buffer->heads - buffer->tails;
    else
        used = buffer->size - buffer->tails + buffer->heads;

    return used >= (buffer->size / 2);
}

uint16_t cb_used(CIRCULAR_BUFFER_T* buffer)
{
    if (buffer->heads >= buffer->tails)
        return buffer->heads - buffer->tails;

    return buffer->size - buffer->tails + buffer->heads;
}

uint8_t cb_is_full(CIRCULAR_BUFFER_T* buffer)
{
    return (buffer->heads + 1) % buffer->size == buffer->tails;
}

void cb_clear(CIRCULAR_BUFFER_T* buffer)
{
    buffer->heads = 0;
    buffer->tails = 0;
    memset(buffer->data, 0, sizeof(DATA_T) * buffer->size);
}

void cb_deinit(CIRCULAR_BUFFER_T* buffer)
{
    free(buffer->data);
    free(buffer);
}


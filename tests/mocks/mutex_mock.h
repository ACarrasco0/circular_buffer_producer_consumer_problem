#ifndef MUTEX_MOCK_H
#define MUTEX_MOCK_H

#include <stdint.h>

typedef struct {
    uint8_t dummy;
} MUTEX_T;

MUTEX_T* mutex_init(void);
void mutex_lock(MUTEX_T* mtx);
void mutex_unlock(MUTEX_T* mtx);
void mutex_deinit(MUTEX_T* mtx);

#endif
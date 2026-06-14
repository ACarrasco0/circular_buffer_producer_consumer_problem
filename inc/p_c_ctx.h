#ifndef CONTEXT_H
#define CONTEXT_H

#include "circular_buffer.h"
#include "stats.h"
#include "mutex.h"
#include <pthread.h>
#include <stdbool.h>


typedef struct {
    CIRCULAR_BUFFER_T *buffer;
    MUTEX_T *mutex;
    pthread_cond_t cond;
    //bool consumer_waiting;
} PC_CONTEXT_T;

#endif
#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H


#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "p_c_ctx.h"

typedef struct{
    PC_CONTEXT_T* ctx;
    uint8_t mode; // 1 direct, 0 Half
}CONSUMER_ARGS_T;

typedef struct 
{
    uint8_t producer_delay;
    PC_CONTEXT_T* ctx;
}PRODUCER_ARGS_T;


void producer_consumer_init(uint16_t buffer_size);
void producer_consumer_deinit(void);
void generate_producer_thread(pthread_t *thread, uint8_t delay_us);
void generate_consumer_thread(pthread_t *thread, uint8_t mode);
#endif
// producer_consumer.c


#include "producer_consumer.h"
#include "circular_buffer.h"
#include "system.h"
#include "mutex.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "stats.h"

static PC_CONTEXT_T pc_ctx;


void producer_consumer_init(uint16_t buffer_size)
{
    data_stats_init();
    
    //assign the context values
    pc_ctx.buffer = cb_init(buffer_size);
    pc_ctx.mutex = mutex_init(); 
    //pc_ctx.consumer_waiting = true;
    //pc_ctx.cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&pc_ctx.cond, NULL);
}

void producer_consumer_deinit(void)
{
    if (pc_ctx.mutex != NULL) {
        mutex_deinit(pc_ctx.mutex);
        pc_ctx.mutex = NULL;
    }
    pthread_cond_destroy(&pc_ctx.cond);
    print_data_stats();
    data_stats_deinit();
    cb_deinit(pc_ctx.buffer);
}

static void *consumer_logic(void *arg)
{
    CONSUMER_ARGS_T *a = (CONSUMER_ARGS_T *)arg;
    PC_CONTEXT_T *ctx = a->ctx;
    const uint16_t HALF = ctx->buffer->size / 2;
    while (1)
    {
        mutex_lock(ctx->mutex);
        while (cb_is_empty(ctx->buffer)) {
            mutex_cond_wait(&ctx->cond, ctx->mutex);
        }

        if (a->mode == 1) // DIRECT
        {
            while (!cb_is_empty(ctx->buffer)){
                DATA_T data = cb_pop(ctx->buffer);
                mutex_unlock(ctx->mutex);
                data_processing(data);
                mutex_lock(ctx->mutex);
            }
        }
        else // HALF (batch draining)
        {
            uint16_t limit = HALF;

            while (limit > 0 && !cb_is_empty(ctx->buffer)){
                DATA_T data = cb_pop(ctx->buffer);
                limit--;

                mutex_unlock(ctx->mutex);
                data_processing(data);
                mutex_lock(ctx->mutex);
            }
        }
        mutex_unlock(ctx->mutex);
    }
    return NULL;
}


// You can generate several in a for loop using pthread_create and pass it an array
// with the maximum number of producers
static void *producer_logic(void *arg)
{
    PRODUCER_ARGS_T *a = (PRODUCER_ARGS_T *)arg;
    PC_CONTEXT_T *ctx = a->ctx;

    while (1)
    {
        DATA_T data_generated;

        data_generated.id = get_number_data_generated();
        data_generated.data = rand();
        data_generated.timestamp = get_tiemstamp_in_us();

        mutex_lock(ctx->mutex);
        cb_push(ctx->buffer, data_generated);
        mutex_cond_signal(&ctx->cond);
        mutex_unlock(ctx->mutex);
        usleep(a->producer_delay);
    }

    return NULL;
}


void generate_producer_thread(pthread_t *thread, uint8_t delay_us)
{
    PRODUCER_ARGS_T *args = malloc(sizeof(PRODUCER_ARGS_T));

    args->producer_delay = delay_us;
    args->ctx = &pc_ctx;

    pthread_create(thread, NULL, producer_logic, args);
}

void generate_consumer_thread(pthread_t *thread, uint8_t mode)
{
    CONSUMER_ARGS_T *args = malloc(sizeof(CONSUMER_ARGS_T));

    args->mode = mode;
    args->ctx = &pc_ctx;

    pthread_create(thread, NULL, consumer_logic, args);
}
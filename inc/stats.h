#ifndef STATS_H
#define STATS_H

#include <stdint.h>
#include  "circular_buffer.h"
#include "mutex.h"

#define BLOCK_SIZE 64

typedef struct
{
    double diff_mean;
    double diff_m2;
    uint32_t diff_max;
    uint32_t diff_min;
    uint16_t num_generated_samples;
    uint16_t num_processed_samples;
    MUTEX_T* mutex;
}STATISTICS_T;

void data_stats_init(void);
void data_stats_deinit(void);
uint16_t get_number_data_generated(void);
void data_processing(DATA_T data_to_process);
void print_data_stats(void);

#endif

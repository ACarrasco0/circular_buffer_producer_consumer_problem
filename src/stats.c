// stats.c

#include "stats.h"
#include "system.h"
#include "circular_buffer.h"
#include "mutex.h"
#include <stdio.h>
#include <stdint.h>

static STATISTICS_T data_stats;
static uint64_t timestamp_start = 0;

void data_stats_init(void)
{
    data_stats.diff_mean             = 0.0;
    data_stats.diff_m2               = 0.0;
    data_stats.diff_max              = 0;
    data_stats.diff_min              = 0xFFFFFFFF;
    data_stats.num_generated_samples = 0;
    data_stats.num_processed_samples = 0;
    timestamp_start = get_tiemstamp_in_us();
    //MUTEX_T* stats_mutex = mutex_init();
    data_stats.mutex = mutex_init();
}

void data_stats_deinit(void)
{
    if (data_stats.mutex != NULL) {
        mutex_deinit(data_stats.mutex);
        data_stats.mutex = NULL;
    }
}

uint16_t get_number_data_generated(void)
{
    mutex_lock(data_stats.mutex);
    uint16_t num_generated = data_stats.num_generated_samples;
    data_stats.num_generated_samples += 1;
    mutex_unlock(data_stats.mutex);
    return num_generated;
}


void data_processing(DATA_T data_to_process)
{
    // not necessary to lock mutex here since this function is only called by
    // the consumer thread. And there is only one consumer thread.
    uint32_t timestamp_diff = (uint32_t)(get_tiemstamp_in_us() - data_to_process.timestamp);
    if(timestamp_diff > data_stats.diff_max) data_stats.diff_max = timestamp_diff;
    if(timestamp_diff < data_stats.diff_min) data_stats.diff_min = timestamp_diff;

    // Welford keeps a running mean and M2, so we avoid accumulating x*x
    // and still get the variance in one pass with bounded state.
    uint16_t n = ++data_stats.num_processed_samples;
    double diff = (double)timestamp_diff - data_stats.diff_mean;
    data_stats.diff_mean += diff / n;
    double diff2 = (double)timestamp_diff - data_stats.diff_mean;
    data_stats.diff_m2 += diff * diff2;
}

void print_data_stats(void)
{
    // Print avg, max, min, std dev, num samples, troughout, etc
    // This is executed at the end of the code to avoid interference
    uint64_t elapsed_us = get_tiemstamp_in_us() - timestamp_start;
    uint64_t avg = 0;
    uint64_t variance = 0;
    uint64_t throughput = 0;
    uint16_t N = data_stats.num_processed_samples;
    
    if (N <= 1) {
        avg = (uint64_t)data_stats.diff_mean;
        variance = 0;
    }
    else {
        avg = (uint64_t)data_stats.diff_mean;
        variance = (uint64_t)(data_stats.diff_m2 / N);
    }
    
    if (elapsed_us > 0) {
        throughput = (data_stats.num_processed_samples * 1000000ULL) / elapsed_us;
    }

    printf("\n");
    printf("Average latency: %ld us\n", avg);
    printf("Maximum latency: %d us\n", data_stats.diff_max);
    printf("Minimum latency: %d us\n", data_stats.diff_min);
    printf("Standard deviation: %ld us\n", variance);
    printf("Number of generated samples: %d \n", data_stats.num_generated_samples);
    printf("Number of processed samples: %d \n", data_stats.num_processed_samples);
    printf("Number of lost samples: %d \n",
        data_stats.num_generated_samples - data_stats.num_processed_samples);
    printf("Elapsed time: %ld seconds \n", elapsed_us / 1000000);
    printf("Throughput: %ld samples/sec \n", throughput);
}
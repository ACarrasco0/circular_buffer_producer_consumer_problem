#include "producer_consumer.h"
#include "system.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    uint16_t buffer_size;
    uint16_t producers;
    uint8_t mode;

    printf("Number of producers: ");
    scanf("%hu", &producers);

    printf("Consumer mode (0=half, 1=direct): ");
    scanf("%hhu", &mode);

    printf("Buffer size: ");
    scanf("%hu", &buffer_size);

    pthread_t *producer_threads = malloc(sizeof(pthread_t) * producers);
    uint8_t *producer_delays = malloc(sizeof(uint8_t) * producers);
    pthread_t consumer_thread;

    for (uint16_t i = 0; i < producers; i++){
        printf("Producer %d delay (us): ", i);
        scanf("%hhu", &producer_delays[i]);
    }

    setup_signals();
    producer_consumer_init(buffer_size);

    for (uint16_t i = 0; i < producers; i++){
        generate_producer_thread( &producer_threads[i], producer_delays[i]);
    }

    generate_consumer_thread(&consumer_thread, mode);
    
    printf("App runing ... \n");
    while(app_running)
    {
        usleep(1000);
    }

    printf("\nData path finished\n");
    for (uint16_t i = 0; i < producers; i++){
        pthread_cancel(producer_threads[i]);
        pthread_join(producer_threads[i], NULL);
    }

    pthread_cancel(consumer_thread);
    pthread_join(consumer_thread, NULL);
    free(producer_threads);
    free(producer_delays);
    producer_consumer_deinit();

    return 0;
}
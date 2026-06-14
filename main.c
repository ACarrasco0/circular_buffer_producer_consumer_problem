//main.c

#include "producer_consumer.h"
#include "system.h"
#include <pthread.h>
#include <stdio.h>

pthread_t thread_producer;
pthread_t thread_consumer;

int main(void)
{
    setup_signals();
    producer_consumer_init(1024);
    generate_producer_thread(&thread_producer, 100);
    generate_consumer_thread(&thread_consumer, 0);

    while(app_running)
    {
       //printf("runin \n");     
        usleep(1000);
    }
    printf("\n");
    printf("Data path finished");
    pthread_cancel(thread_producer);
    pthread_cancel(thread_consumer);
    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);
    producer_consumer_deinit();
    
}
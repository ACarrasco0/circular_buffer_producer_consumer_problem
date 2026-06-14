#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
} MUTEX_T;

MUTEX_T* mutex_init(void);
void mutex_lock(MUTEX_T* mtx);
void mutex_unlock(MUTEX_T* mtx);
void mutex_cond_wait(pthread_cond_t *cond, MUTEX_T *mtx);
void mutex_cond_signal(pthread_cond_t *cond);
void mutex_deinit(MUTEX_T* mtx);

#endif //MUTEX_H
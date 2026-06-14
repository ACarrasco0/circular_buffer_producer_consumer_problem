#include "mutex.h"
#include "stdlib.h"

MUTEX_T* mutex_init(void)
{
    MUTEX_T* new_mutex = (MUTEX_T*)malloc(sizeof(MUTEX_T));
    if (!new_mutex) return NULL;

    pthread_mutex_init(&new_mutex->mutex, NULL);
    return new_mutex;
}

void mutex_lock(MUTEX_T* mtx)
{
    pthread_mutex_lock(&mtx->mutex);
}

void mutex_unlock(MUTEX_T* mtx)
{
    pthread_mutex_unlock(&mtx->mutex);
}

void mutex_cond_wait(pthread_cond_t *cond, MUTEX_T *mtx)
{
    pthread_cond_wait(cond,&mtx->mutex);
}

void mutex_cond_signal(pthread_cond_t *cond)
{
    pthread_cond_signal(cond);
}  

void mutex_deinit(MUTEX_T* mtx)
{
    pthread_mutex_destroy(&mtx->mutex);
    free(mtx);
}
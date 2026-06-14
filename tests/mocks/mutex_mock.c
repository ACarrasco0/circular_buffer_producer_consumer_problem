#include "mutex_mock.h"
#include <stdlib.h>

MUTEX_T* mutex_init(void)
{
    return (MUTEX_T*)malloc(sizeof(MUTEX_T));
}

void mutex_lock(MUTEX_T* mtx)
{
    (void)mtx;
}

void mutex_unlock(MUTEX_T* mtx)
{
    (void)mtx;
}

void mutex_deinit(MUTEX_T* mtx)
{
    free(mtx);
}
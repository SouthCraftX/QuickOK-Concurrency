#pragma once
#include "errors.h"
#define __QO_POSIX_MUTEX_H__

// for debug
#include "../../../mutex.h"

#if !defined(__QO_MUTEX_H__)
#   error "Do not include this header directly. Use mutex.h instead"
#endif 

#include <pthread.h>

struct _QO_Mutex
{
    pthread_mutex_t __mutex;
};

QO_GLOBAL_UNIQUE
qo_stat_t
qo_mutex_init(
    QO_Mutex *  p_mutex
) {
    // EBUSY is what we can only get when calling pthread_mutex_init
    return pthread_mutex_init(&p_mutex->__mutex, NULL) ?
           QO_ALREADY : QO_OK;
}


QO_GLOBAL_UNIQUE
qo_stat_t
qo_mutex_destroy(
    QO_Mutex *  p_mutex
) {
    return  pthread_mutex_destroy(&p_mutex->__mutex) ?
            __qo_mutex_destroying_error(ret) : QO_OK;
}

QO_GLOBAL_UNIQUE
void
qo_mutex_lock(
    QO_Mutex *  p_mutex
) {
    return pthread_mutex_lock(&p_mutex->__mutex) ? 
            __qo_mutex_locking_error() : QO_OK;
}

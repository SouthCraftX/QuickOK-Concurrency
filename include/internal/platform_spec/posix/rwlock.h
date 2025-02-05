#pragma once
#include "errors.h"
#include <cerrno>
#define __QO_POSIX_RWLOCK_H__

// for debug
#include "../../../rwlock.h"

#if !defined(__QO_RWLOCK_H__)
#error "Do not include this file directly。 Use rwlock.h instead"
#endif

#include <pthread.h>

struct _QO_RWLock
{
    pthread_rwlock_t __lock;
};

QO_GLOBAL_UNIQUE
void
qo_rwlock_destroy(
    QO_RWLock * p_lock
) {
    if (p_lock)
        pthread_rwlock_destroy(&p_lock->__lock);
}

QO_GLOBAL_UNIQUE
void
qo_rwlock_init(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_init(&p_lock->__lock , NULL);
    if (ret)
        __qo_rwlock_init_error(ret);
}

QO_GLOBAL_UNIQUE
void
qo_rwlock_rdlock(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_rdlock(&p_lock->__lock);
    if (ret)
        __qo_rwlock_rdlock_error(ret);
}

QO_GLOBAL_UNIQUE
void
qo_rwlock_wrlock(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_wrlock(&p_lock->__lock);
    if (ret)
        __qo_rwlock_wrlock_error(ret);
}

QO_GLOBAL_UNIQUE
qo_bool_t
qo_rwlock_try_rdlock(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_tryrdlock(&p_lock->__lock);
    switch (ret) 
    {
        case 0:
            return qo_true;
        case EBUSY:
            return qo_false;
        default:
            __qo_rwlock_rdlock_error(ret);
    }
}

QO_GLOBAL_UNIQUE
qo_bool_t
qo_rwlock_try_wrlock(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_trywrlock(&p_lock->__lock);
    switch (ret) 
    {
        case 0:
            return qo_true;
        case EBUSY: 
            return qo_false;
        default:
            __qo_rwlock_wrlock_error(ret);
    }
}

QO_GLOBAL_UNIQUE
void
qo_rwlock_unlock(
    QO_RWLock * p_lock
) {
    QO_ASSERT(p_lock);
    int ret = pthread_rwlock_unlock(&p_lock->__lock);
    if (ret)
        __qo_rwlock_unlock_error(ret);
}




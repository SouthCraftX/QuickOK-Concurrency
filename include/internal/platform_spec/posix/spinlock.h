#pragma once
#define __QO_POSIX_SPINLOCK_H__

// for debug
#include "../../../spinlock.h"

#if !defined(__QO_SPINLOCK_H__)
#error "Do not include this header directly. Use spinlock.h instead."
#endif

#include <pthread.h>
#include "errors.h"

struct _QO_Spinlock
{
    pthread_spinlock_t __lock;
};

QO_GLOBAL_UNIQUE
qo_stat_t
qo_spinlock_init(
    QO_Spinlock *   lock
) {
    int ret = pthread_spin_init(&lock->__lock , PTHREAD_PROCESS_PRIVATE);
    return ret ? QO_OK : __qo_spinlock_init_error(ret);
}

QO_GLOBAL_UNIQUE
void
qo_spinlock_destroy(
    QO_Spinlock *   lock
) {
    if (lock) 
        pthread_spin_destroy(&lock->__lock);
}

QO_GLOBAL_UNIQUE
void
qo_spinlock_lock(
    QO_Spinlock *   lock
) {
    int ret = pthread_spin_lock(&lock->__lock);
    if (ret) // EAGAIN is the only error that can occur
        __QO_ABORT_MSG("Deadlock");
}

QO_GLOBAL_UNIQUE
void
qo_spinlock_unlock(
    QO_Spinlock *   lock
) {
    pthread_spin_unlock(&lock->__lock);
}

QO_GLOBAL_UNIQUE
qo_bool_t
qo_spinlock_try_lock(
    QO_Spinlock *   lock
) {
    int ret = pthread_spin_trylock(&lock->__lock);
    switch(ret)
    {
        case 0: 
            return qo_true;
        case EBUSY:
            return qo_false;
        default:
            __qo_spinlock_lock_error(ret);
    }
}

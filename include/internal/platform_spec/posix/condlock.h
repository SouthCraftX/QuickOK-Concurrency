#pragma once
#define __QO_POSIX_CONDLOCK_H__

// for debug
#include "../../../condlock.h"

#if !defined(__QO_CONDLOCK_H__)
#error "Do not include this header directly. Use condlock.h instead."
#endif

#include <pthread.h>

struct _QO_CondLock 
{
    pthread_cond_t  cond;
    pthread_mutex_t mutex;
};

QO_GLOBAL_UNIQUE
void
qo_condlock_init(
    QO_CondLock *   condlock
) {
    QO_ASSERT(condlock);
}


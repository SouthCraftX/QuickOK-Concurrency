#pragma once

#include "../../base.h"

#include <cerrno>
#include <errno.h>

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_spinlock_init_error(int ret)
{
    switch (ret) 
    {
        case EAGAIN:
            __QO_ABORT_MSG("Deadlock");
        case ENOMEM:
            return QO_OUT_OF_MEMORY;
        default:
            __QO_BUG("Unexpected errno");
    }
}

QO_GLOBAL_UNIQUE
void
__qo_spinlock_lock_error(int ret)
{
    switch (ret) 
    {
        case EINVAL:
            __QO_BUG("Invalid lock");
        case EAGAIN:
            __QO_ABORT_MSG("Already holding the lock");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE
void
__qo_rwlock_rdlock_error(int ret)
{
    switch (ret) 
    {
        case EINVAL:
            __QO_BUG("Invalid lock");
        case EAGAIN:
            __QO_ABORT_MSG("Max readers reached");
        case EDEADLK: 
            __QO_ABORT_MSG("Deadlock");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_LOCAL
void
__qo_rwlock_init_error(
    int ret
){
    switch (ret) 
    {
        case EBUSY:
            __QO_ABORT_MSG("Lock already initialized");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE
void
__qo_rwlock_wrlock_error(
    int ret
){
    switch (ret) 
    {
        case EINVAL:
            __QO_BUG("Invalid lock");
        case EDEADLK: 
            __QO_ABORT_MSG("Already owning the lock");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE
void
__qo_rwlock_unlock_error(
    int ret
) {
    switch (ret) 
    {
        case EINVAL:
            __QO_BUG("Invalid lock");
        case EPERM:
            __QO_BUG("Not owning the lock");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE
void
__qo_mutex_init_error(
    int ret
){
    switch (ret) 
    {
        case EAGAIN:
            __QO_ABORT_MSG("The system lacked the necessary resources (other "
                           "than memory) to initialize the mutex");
        case ENOMEM:
            __QO_ABORT_MSG("No enough memory to initialize the mutex");
        case EPERM:
            __QO_ABORT_MSG("The caller does not have the privilege to initialize the mutex");
        case EBUSY:
            __QO_ABORT_MSG("Already initialized");
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE QO_NO_SIDE_EFFECTS
qo_stat_t
__qo_mutex_destroying_error(
    int ret
){
    switch (ret) 
    {
        case EBUSY:
            return QO_ACCESS_VIOLATED; // Still locked
        case EINVAL:
            return QO_INVALID_HANDLE;
        default:
            __QO_BUG("Unexpected return value");
    }
}

QO_GLOBAL_UNIQUE QO_NO_SIDE_EFFECTS
qo_stat_t
__qo_mutex_locking_error(
    int ret
){
    switch (ret) 
    {
        
    }
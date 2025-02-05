#pragma once
#include <winternl.h>
#define __QO_WIN32_THREAD_H__

// for debug
#include "../../../thread.h"

#if !defined(__QO_THREAD_H__)
#error "Do not include this file directly. Use thread.h instead."
#endif

#include <synchapi.h>
#include <processthreadsapi.h>
#include "errors.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Thread
{
    HANDLE handle;
};

QO_GLOBAL_UNIQUE
qo_stat_t
qo_thread_create(
    QO_Thread *     p_thread ,
    qo_pointer_t    start_routine ,
    qo_pointer_t    argument ,
    qo_size_t       stack_size 
) {
    QO_ASSERT(p_thread && start_routine);
    HANDLE handle = CreateThread(
        NULL , stack_size, (LPTHREAD_START_ROUTINE)start_routine , argument , 0 , NULL
    );
    if (handle)
    {
        p_thread->handle = handle;
        return QO_OK;
    }

}

QO_GLOBAL_UNIQUE QO_FORCE_INLINE
void
qo_thread_get_self(
    QO_Thread * p_thread
) {
    QO_ASSERT(p_thread);
    p_thread->handle = GetCurrentThread();
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_thread_kill(
    QO_Thread * p_thread
) {
    QO_ASSERT(p_thread);
    return TerminateThread(p_thread->handle, -1) ? QO_OK : __qo_thread_killing_error();
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_thread_join(
    QO_Thread * p_thread
) {
    QO_ASSERT(p_thread);
    return (WaitForSingleObject(p_thread->handle, INFINITE) == WAIT_OBJECT_0 )? 
            QO_OK :
            __qo_thread_joining_error();
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_thread_is_active(
    QO_Thread * p_thread , 
    qo_bool_t * p_active
) {
    QO_ASSERT(p_active && p_thread);
    qo_stat_t ret = QO_OK;
    switch (WaitForSingleObject(p_thread->handle, 0)) 
    {
        case WAIT_OBJECT_0:
            *p_active = qo_false;
            break;
        case WAIT_TIMEOUT:
            *p_active = qo_true;
            break;
        default:
            ret = __qo_thread_is_active_error();
    }
    return ret;
}

QO_GLOBAL_UNIQUE 
qo_stat_t
qo_thread_set_priority(
    QO_Thread *         p_thread ,
    QO_RoutinePriority  priority
) {
    QO_ASSERT((priority >= QO_ROUTINE_BACKGROUND && priority <= QO_ROUTINE_CRITICAL) && p_thread);
    const DWORD priority_table[] = {
        THREAD_MODE_BACKGROUND_BEGIN ,
        THREAD_PRIORITY_LOWEST ,
        THREAD_PRIORITY_BELOW_NORMAL ,
        THREAD_PRIORITY_NORMAL ,
        THREAD_PRIORITY_ABOVE_NORMAL ,
        THREAD_PRIORITY_HIGHEST ,
        THREAD_PRIORITY_TIME_CRITICAL
    };
    return SetThreadPriority(p_thread->handle, priority_table[priority]) ?
            QO_OK : __qo_thread_priority_setting_error();   
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_thread_get_priority(
    QO_Thread *             p_thread , 
    QO_RoutinePriority *    p_priority
) {
    qo_stat_t ret = QO_OK;
    QO_ASSERT(p_priority && p_thread);
    DWORD win_pririty = GetThreadPriority(p_thread->handle);
    if (win_pririty == THREAD_PRIORITY_ERROR_RETURN) 
        ret = __qo_thread_priority_getting_error();
    else if (win_pririty <= THREAD_PRIORITY_IDLE)
        *p_priority = QO_ROUTINE_BACKGROUND;
    else if (win_pririty == THREAD_PRIORITY_LOWEST)
        *p_priority = QO_ROUTINE_LOWER;
    else if (win_pririty == THREAD_PRIORITY_BELOW_NORMAL)
        *p_priority = QO_ROUTINE_LOW;
    else if (win_pririty == THREAD_PRIORITY_NORMAL)
        *p_priority = QO_ROUTINE_NORMAL;
    else if (win_pririty == THREAD_PRIORITY_ABOVE_NORMAL)
        *p_priority = QO_ROUTINE_HIGH;
    else if (win_pririty == THREAD_PRIORITY_HIGHEST)   
        *p_priority = QO_ROUTINE_HIGHER;
    else if (win_pririty == THREAD_PRIORITY_TIME_CRITICAL)
        *p_priority = QO_ROUTINE_CRITICAL;
    return ret;
}

// Add __QO_WIN32 prefix to avoid possible name conflicts in case users want to use
// THREAD_BASIC_INFORMATION and define it in their code)
typedef struct __QO_WIN32_THREAD_BASIC_INFORMATION 
{
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    ULONG UniqueProcessId;
    ULONG UniqueThreadId;
    ULONG_PTR AffinityMask;
    LONG Priority;
    LONG BasePriority;
    ULONG SuspendCount;  
} _QO_WIN32_THREAD_BASIC_INFORMATION;

qo_stat_t
qo_thread_suspend(
    QO_Thread * p_thread
) {
    QO_ASSERT(p_thread);

    // Is the thread already suspended?
    _QO_WIN32_THREAD_BASIC_INFORMATION tbi;
    ULONG returned_length;
    NTSTATUS ret =  NtQueryInformationThread(
        p_thread->handle , ThreadBasicInformation , &tbi , sizeof(tbi) , &returned_length
    ); // TODO: error handling
    if(tbi.SuspendCount)
        return QO_ALREADY;

    return SuspendThread(p_thread->handle) != (DWORD)-1 ? 
            QO_OK : __qo_thread_suspending_error();
}

QO_GLOBAL_UNIQUE QO_FORCE_INLINE
void
qo_thread_suspend_self(
    qo_size_t milliseconds
) {
    Sleep(milliseconds);
}

qo_stat_t
qo_thread_resume(
    QO_Thread * p_thread
) {
    QO_ASSERT(p_thread);
    return ResumeThread(p_thread->handle) != (DWORD)-1 ? 
            QO_OK : __qo_thread_resuming_error();
}

#if defined(__cplusplus)
}
#endif // __cplusplus
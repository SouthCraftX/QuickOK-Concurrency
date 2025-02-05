#pragma once
#include <errhandlingapi.h>
#include <ntstatus.h>
#include <winbase.h>
#define __QO_WIN32_PROCESS_ERRORS_H__

// for debug
#include "process.h"

#if !defined (__QO_WIN32_PROCESS_H__)
#error "Do not include this file directly. Use process.h instead."
#endif 

QO_GLOBAL_LOCAL QO_NO_SIDE_EFFECTS 
qo_stat_t
__qo_process_suspending_error(
    NTSTATUS status
) {
    switch (status) {
        case STATUS_PROCESS_IS_TERMINATING:
            return QO_ACCESS_VIOLATED;
        case STATUS_INVALID_HANDLE:
        case STATUS_INVALID_PARAMETER:
            return QO_INVALID_HANDLE;
        case STATUS_ACCESS_DENIED:
            return QO_PERMISSION_DENIED;
        default:
            return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_env_setting_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        case ERROR_NOT_ENOUGH_MEMORY:   return QO_OUT_OF_MEMORY;
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;

    }
}

QO_GLOBAL_LOCAL QO_NO_SIDE_EFFECTS QO_FORCE_INLINE
qo_stat_t
__qo_process_resuming_error(
    NTSTATUS status
) {
    // They share similar errors
    return __qo_process_suspending_error(status);
}

QO_GLOBAL_LOCAL QO_PURE
qo_stat_t
__qo_process_killing_error()
{
    switch (GetLastError())
    {
        case ERROR_INVALID_HANDLE:      return  QO_INVALID_HANDLE;
        case ERROR_ACCESS_DENIED:       return  QO_PERMISSION_DENIED;
        default:                        return  QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_process_pid_opening_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_PARAMETER: 
        case ERROR_FILE_NOT_FOUND:      return QO_NOT_FOUND;
        case ERROR_EVALUATION_REQUIRED:
        case ERROR_NOACCESS:
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_PARTIAL_COPY:        return QO_NOT_SUPPORTED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_process_priority_getting_error()
{
    switch (GetLastError()) 
    {
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_PARTIAL_COPY:        return QO_NOT_SUPPORTED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_process_priority_setting_error()
{
    switch (GetLastError()) 
    {
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_INVALID_PARAMETER:   QO_BUG("Unexpected parameter error");
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_killing_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_PARAMETER:
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_NOT_SUPPORTED:
        case ERROR_ACCESS_DISABLED_BY_POLICY:
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_joining_error()
{
    switch (GetLastError()) 
    {
        // Handle is null or dwMilliseconds exceeds MAXDWORD but not INFINITE
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_NOT_SUPPORTED:
        case ERROR_PRIVILEGE_NOT_HELD:   
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_is_active_error()
{
    // Both of them use WaitForSingleObject
    return __qo_thread_joining_error();
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_priority_setting_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_INVALID_PARAMETER:   QO_BUG("Unexpected parameter error");
        case ERROR_PRIVILEGE_NOT_HELD:  
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_priority_getting_error()
{
    // They share similar errors
    return __qo_thread_priority_setting_error();
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_suspending_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_PARAMETER:
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_NOT_SUPPORTED:   // `System`'s threads are not allowed to be suspended
        case ERROR_INVALID_FUNCTION:   // The thread has already ended or system doesn't allow it
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        default:                        return QO_UNKNOWN_ERROR;
    }
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_resuming_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_PARAMETER:
        case ERROR_INVALID_HANDLE:      return QO_INVALID_HANDLE;
        case ERROR_THREAD_NOT_SUSPENDED: return QO_ALREADY;
        case ERROR_PRIVILEGE_NOT_HELD:  // THREAD_SUSPEND_RESUME / SeDebugPrivilege
        case ERROR_NOT_SUPPORTED:   
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_TOO_MANY_THREADS     return QO_NO_RESOURCES;
        default:                        return QO_UNKNOWN_ERROR;
}

QO_GLOBAL_UNIQUE QO_PURE
qo_stat_t
__qo_thread_creating_error()
{
    switch (GetLastError()) 
    {
        case ERROR_INVALID_ADDRESS:   
        case ERROR_STACK_OVERFLOW:   
        case ERROR_INVALID_FUNCTION: // lpStartAddress error. Very rare
        case ERROR_INVALID_PARAMETER:   return QO_INVALID_ARG;
        case ERROR_EXCEEDING_PAGED_POOL_QUOTA:
        case ERROR_COMMIT_LIMIT:
        case ERROR_NOT_ENOUGH_MEMORY:   return QO_OUT_OF_MEMORY;
        case ERROR_PRIVILEGE_NOT_HELD:  // SeCreateThreadTokenPrivilege
        case ERROR_NOT_SUPPORTED:   
        case ERROR_ACCESS_DENIED:       return QO_PERMISSION_DENIED;
        case ERROR_DS_THREAD_LIMIT_EXCEEDED:
        case ERROR_TOO_MANY_TCBS:       return QO_TOO_MANY;
        case ERROR_TOO_MANY_OPEN_FILES: return QO_NO_RESOURCES;
        case ERROR_POSSIBLE_DEADLOCK:   QO_BUG("Possible deadlock");
        default:                        return QO_UNKNOWN_ERROR;
    }
}
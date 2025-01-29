#pragma once
#include <ntstatus.h>
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
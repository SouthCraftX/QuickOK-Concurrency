#pragma once
#include <cstddef>
#include <processenv.h>
#define __QO_WIN32_PROCESS_H__

// for debug
#include "../../../process.h"

#if !defined(__QO_PROCESS_H__)
#error "Do not include this header directly. Use process.h instead."
#endif // __QO_PROCESS_H__

#include <processthreadsapi.h>
#include <ntstatus.h>
#include <ntdef.h>
#include <errhandlingapi.h>
#include <winternl.h>
#include <heapapi.h>

#include "errors.h"

// Hidden APIs in Ntdll.dll

__declspec(dllimport) NTSTATUS NTAPI 
NtSuspendProcess(
    HANDLE ProcessHandle
);

__declspec(dllimport) NTSTATUS NTAPI 
NtResumeProcess(
    HANDLE ProcessHandle
);

struct _QO_Process
{
    HANDLE handle;
};

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_suspend(
    QO_Process *    p_process
) {
    NTSTATUS ret = NtSuspendProcess(p_process->handle);
    return ret ? __qo_process_suspending_error(ret) : QO_OK;
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_resume(
    QO_Process *    p_process
) {
    NTSTATUS ret = NtResumeProcess(p_process->handle);
    return ret ? __qo_process_resuming_error(ret) : QO_OK;
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_set_env(
    qo_ccstring_t   key ,
    qo_ccstring_t   value
) {
    if(!value)
        return QO_NOT_SUPPORTED;
    return SetEnvironmentVariableA(key , value) ? __qo_env_setting_error() : QO_OK;
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_get_pid(
    QO_Process *    p_process ,
    qo_uint32_t *   p_pid
) {
    DWORD ret = GetProcessId(p_process->handle);
    return ret ? QO_OK : QO_INVALID_HANDLE;
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_from_pid(
    QO_Process *    p_process ,
    qo_uint32_t     pid
) {
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
    if (handle) 
    {
        p_process->handle = handle;
        return QO_OK;
    }
    return __qo_process_pid_opening_error();
}

QO_GLOBAL_UNIQUE
void
qo_process_exit_self(
    qo_stat_t status
) {
    ExitProcess(status);
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_kill(
    QO_Process *    p_process
) {
    TerminateProcess(p_process->handle , -1);
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_dismiss(
    QO_Process *    p_process
) {
    if (p_process && p_process->handle) 
        CloseHandle(p_process->handle);
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_get_priority(
    QO_Process *            p_process , 
    QO_RoutinePriority *    p_priority
) {
    qo_stat_t ret = QO_OK;
    DWORD priority = GetPriorityClass(p_process->handle);

    switch (priority)
    {
        case IDEL_PRIORITY_CLASS:
            *p_priority = QO_ROUTINE_LOWER;
            break;
        
        case BELOW_NORMAL_PRIORITY_CLASS:
            *p_priority = QO_ROUTINE_LOW;
            break;

        case NORMAL_PRIORITY_CLASS:
            *p_priority = QO_ROUTINE_NORMAL;
            break;

        case ABOVE_NORMAL_PRIORITY_CLASS:
            *p_priority = QO_ROUTINE_HIGH;
            break;

        case HIGH_PRIORITY_CLASS:   
            *p_priority = QO_ROUTINE_HIGHER;
            break;
        
        case REALTIME_PRIORITY_CLASS:
            *p_priority = QO_ROUTINE_CRITICAL;
            break;

        default:
            ret = __qo_process_priority_getting_error();
    }
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_set_priority(
    QO_Process *            p_process ,
    QO_RoutinePriority      priority
) {
    DWORD priority_class;
    switch (priority)
    {
        case QO_ROUTINE_LOWER:
            priority_class = IDEL_PRIORITY_CLASS;
            break;

        case QO_ROUTINE_LOW:
            priority_class = BELOW_NORMAL_PRIORITY_CLASS;
            break;

        case QO_ROUTINE_NORMAL:
            priority_class = NORMAL_PRIORITY_CLASS;
            break;

        case QO_ROUTINE_HIGH:
            priority_class = ABOVE_NORMAL_PRIORITY_CLASS;
            break;

        case QO_ROUTINE_HIGHER:
            priority_class = HIGH_PRIORITY_CLASS;
            break;

        case QO_ROUTINE_CRITICAL:
            priority_class = REALTIME_PRIORITY_CLASS;
            break;

        default:
            return QO_INVALID_ARG;
    }
    return SetPriorityClass(p_process->handle , priority_class) ?
        QO_OK : __qo_process_priority_setting_error();
}

QO_GLOBAL_UNIQUE
qo_stat_t
qo_process_get_thread_count(
    QO_Process *    p_process , 
    qo_uint32_t *   p_count
) {
    qo_size_t   process_info_len;
    qo_uint32_t count = 0;
    DWORD       pid = GetProcessId(p_process->handle);
    SYSTEM_PROCESS_INFORMATION process_info;
    NtQuerySystemInformation(SystemProcessInformation  , NULL , 0 , &process_info_len);
    PVOID buffer = HeapAlloc(GetProcessHeap() , 0 , process_info_len);
    PSYSTEM_PROCESS_INFORMATION p_process_info = (PSYSTEM_PROCESS_INFORMATION)buffer;
    while (p_process_info)
    {
        
    }
}
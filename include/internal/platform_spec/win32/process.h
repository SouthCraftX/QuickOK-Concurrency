#pragma once
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

QO_GLOBAL_LOCAL
qo_stat_t
qo_process_from_pid(
    QO_Process *    p_process ,
    qo_uint32_t     pid
) {

}
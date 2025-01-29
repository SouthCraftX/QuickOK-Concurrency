#pragma once
#define __QO_PROCESS_H__

#include "thread.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Process;
typedef struct _QO_Process QO_Process;

qo_stat_t
qo_process_from_pid(
    QO_Process *    p_process ,
    qo_uint32_t     pid
) QO_NONNULL(1);

qo_stat_t
qo_process_get_pid(
    QO_Process *    p_process ,
    qo_uint32_t *   p_pid
) QO_NONNULL(1 , 2);

qo_stat_t
qo_process_kill(
    QO_Process *    p_process 
) QO_NONNULL(1);

qo_stat_t
qo_process_suspend(
    QO_Process *    p_process
) QO_NONNULL(1);

qo_stat_t
qo_process_resume(
    QO_Process *    p_process
) QO_NONNULL(1);

qo_stat_t
qo_process_set_priority(
    QO_Process *        p_process ,
    QO_RoutinePriority  priority
) QO_NONNULL(1);

qo_stat_t
qo_process_get_priority(
    QO_Process *            p_process ,
    QO_RoutinePriority *    p_priority
) QO_NONNULL(1 , 2);

QO_NORETURN
void
qo_process_exit_self(
    qo_stat_t  status
);


#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/process.h"
#else
#   include "internal/platform_spec/posix/process.h"
#endif // QO_PLATFORM(WINDOWS)
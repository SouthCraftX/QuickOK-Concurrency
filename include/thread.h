#pragma once
#define __QO_THREAD_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

enum QO_RoutinePriority 
{
    QO_ROUTINE_BACKGROUND = 0 ,
    QO_ROUTINE_LOWER ,
    QO_ROUTINE_LOW ,
    QO_ROUTINE_NORMAL ,
    QO_ROUTINE_HIGH ,
    QO_ROUTINE_HIGHER ,
    QO_ROUTINE_CRITICAL
};

struct _QO_Thread;
typedef struct _QO_Thread QO_Thread;

qo_stat_t
qo_thread_create(
    QO_Thread *     p_thread ,
    qo_pointer_t    start_routine ,
    qo_pointer_t    argument ,
    qo_size_t       stack_size 
) QO_NONNULL(1 , 2);

void
qo_thread_get_self(
    QO_Thread * p_thread
) QO_NONNULL(1);

qo_stat_t
qo_thread_join(
    QO_Thread *     p_thread 
) QO_NONNULL(1);

qo_stat_t
qo_thread_join_many(
    QO_Thread *     thread_array
) QO_NONNULL(1);

QO_NORETURN
qo_stat_t
qo_thread_exit_self(
    qo_stat_t       status
);

void
qo_thread_yield();

qo_stat_t
qo_thread_suspend(
    QO_Thread *     p_thread
) QO_NONNULL(1);

qo_stat_t
qo_thread_resume(
    QO_Thread *     p_thread
) QO_NONNULL(1);

void
qo_thread_suspend_self(
    qo_size_t       milliseconds
);

qo_stat_t
qo_thread_kill(
    QO_Thread *     p_thread
) QO_NONNULL(1);

qo_stat_t
qo_thread_is_active(
    QO_Thread *     p_thread ,
    qo_bool_t *     p_active
) QO_NONNULL(1 , 2);

qo_bool_t
qo_thread_is_equal(
    QO_Thread *     p_x ,
    QO_Thread *     p_y
) QO_NONNULL(1 , 2);

qo_stat_t
qo_thread_get_exit_code(
    QO_Thread *     p_thread ,
    qo_stat_t *     p_exit_code
) QO_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(POSIX)
#   include "internal/platform_spec/posix/thread.h"
#elif QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/thread.h"
#endif // QO_PLATFORM
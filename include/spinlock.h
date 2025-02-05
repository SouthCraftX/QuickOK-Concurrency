#pragma once
#define __QO_SPINLOCK_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Spinlock;
typedef struct _QO_Spinlock QO_Spinlock;

qo_stat_t 
qo_spinlock_init(
    QO_Spinlock *   p_lock
) QO_NONNULL(1);

void
qo_spinlock_destroy(
    QO_Spinlock *   p_lock
);

void
qo_spinlock_lock(
    QO_Spinlock *   p_lock
) QO_NONNULL(1);

qo_bool_t
qo_spinlock_try_lock(
    QO_Spinlock *   p_lock
) QO_NONNULL(1);

void
qo_spinlock_unlock(
    QO_Spinlock *   p_lock
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus

#if QO_PLATFORM(WINDOWS)
#   include "internal/platform_spec/win32/spinlock.h"
#else
#   include "internal/platform_spec/posix/spinlock.h"
#endif 
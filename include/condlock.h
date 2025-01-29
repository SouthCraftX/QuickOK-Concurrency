#pragma once
#define __QO_CONDLOCK_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_CondLock;
typedef struct _QO_CondLock QO_CondLock;

void
qo_condlock_init(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_destroy(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_lock(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_unlock(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_release(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_wait(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_wake(
    QO_CondLock *   condlock
) QO_NONNULL(1);

void
qo_condlock_wake_all(
    QO_CondLock *   condlock
) QO_NONNULL(1);


#if defined(__cplusplus)
}
#endif // __cplusplus
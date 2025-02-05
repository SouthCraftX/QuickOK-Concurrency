#pragma once
#define __QO_RWLOCK_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_RWLock;
typedef struct _QO_RWLock QO_RWLock;

void
qo_rwlock_init(
    QO_RWLock * p_lock
) QO_NONNULL(1);

void
qo_rwlock_destroy(
    QO_RWLock * p_lock
);

void
qo_rwlock_rdlock(
    QO_RWLock * p_lock
) QO_NONNULL(1);

void
qo_rwlock_wrlock(
    QO_RWLock * p_lock
) QO_NONNULL(1);

qo_bool_t
qo_rwlock_try_rdlock(
    QO_RWLock * p_lock
) QO_NONNULL(1);

qo_bool_t
qo_rwlock_try_wrlock(
    QO_RWLock * p_lock
) QO_NONNULL(1);

void
qo_rwlock_unlock(
    QO_RWLock * p_lock
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus
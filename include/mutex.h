#pragma once
#define __QO_MUTEX_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Mutex;
typedef struct _QO_Mutex QO_Mutex;

qo_stat_t
qo_mutex_init(
    QO_Mutex *  p_mutex
) QO_NONNULL(1);

qo_stat_t
qo_mutex_destroy(
    QO_Mutex *  p_mutex
) QO_NONNULL(1);

qo_stat_t
qo_mutex_lock(
    QO_Mutex *  p_mutex
) QO_NONNULL(1);

qo_stat_t
qo_mutex_try_lock(
    QO_Mutex *  p_mutex
) QO_NONNULL(1);

qo_stat_t
qo_mutex_unlock(
    QO_Mutex *  p_mutex
) QO_NONNULL(1);

#if defined(__cplusplus)
}
#endif // __cplusplus
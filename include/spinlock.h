#pragma once
#define __QO_SPINLOCK_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Spinlock;
typedef struct _QO_Spinlock QO_Spinlock;

void 
qo_spinlock_init(
    QO_Spinlock *   lock
) QO_NONNULL(1);

void


#if defined(__cplusplus)
}
#endif // __cplusplus
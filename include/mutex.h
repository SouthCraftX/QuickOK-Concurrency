#pragma once
#define __QO_MUTEX_H__

#include "internal/base.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QO_Mutex;
typedef struct _QO_Mutex QO_Mutex;

void
qo_mutex_init(
    QO_Mutex *  p_mutex
);



#if defined(__cplusplus)
}
#endif // __cplusplus
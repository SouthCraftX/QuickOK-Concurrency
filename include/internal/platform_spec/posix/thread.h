#pragma once
#define __QO_POSIX_THREAD_H__

#if !defined(__QO_THREAD_H__)
#error "Do not include this file directly. Use thread.h instead."
#endif

#include <pthread.h>

struct _QO_Thread
{
    pthread_t thread;
};



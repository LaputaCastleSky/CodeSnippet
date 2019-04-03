#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include <pthread.h>

typedef struct thread_task_s{
    void (*handle)(void *arg);
    void *arg;
    struct thread_task_s *next;
}thread_task_t;

typedef struct{
    thread_task_t *first;
    thread_task_t **last;
}thread_pool_queue_t;

typedef struct thread_pool_s{
    int threads;
    thread_pool_queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}thread_pool_t;

/*t*/
thread_pool_t *thread_pool_init(int threads);
void thread_pool_destroy(thread_pool_t *pool);
void thread_pool_task_post(thread_pool_t *pool, thread_task_t *task);

#endif

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "threadpool.h"
#include "common.h"

#define thread_pool_queue_init(q) \
    (q)->first = NULL; \
    (q)->last = &(q)->first

void *thread_pool_cycle(void *arg);

void *thread_pool_cycle(void *arg){
    thread_pool_t *pool = (thread_pool_t *)arg;
    thread_task_t *task = NULL;

    for(;;){
        if (OK != pthread_mutex_lock(&pool->mutex)){
            return NULL;
        }

        while(pool->queue.first == NULL){
            if(OK != pthread_cond_wait(&pool->cond, &pool->mutex)){
                pthread_mutex_unlock(&pool->mutex);
                return NULL;
            }
        }

        task = pool->queue.first;
        pool->queue.first = task->next;

        if(pool->queue.first == NULL){
            pool->queue.last = &pool->queue.first;
        }

        pthread_mutex_unlock(&pool->mutex);

        task->handle(task->arg);
    }
    return NULL;
}

void thread_pool_task_post(thread_pool_t *pool, thread_task_t *task){
    pthread_mutex_lock(&pool->mutex);

    *pool->queue.last = task;
    pool->queue.last = &task->next;

    if(OK != pthread_cond_signal(&pool->cond)){
        pthread_mutex_unlock(&pool->mutex);
        return;
    }

    pthread_mutex_unlock(&pool->mutex);
}

thread_pool_t *thread_pool_init(int threads){
    int i = 0;
    pthread_t tid;
    thread_pool_t *pool = NULL;

    pool = (thread_pool_t*)malloc(sizeof(thread_pool_t));
    if(pool == NULL){
        printf("malloc thread_pool_t failed.");
        return NULL;
    }

    pool->threads = threads;

    thread_pool_queue_init(&pool->queue);

    if(OK != pthread_mutex_init(&pool->mutex, NULL)){
        printf("pthread_mutex_init error.\n");
        return NULL;
    }
    
    if(OK != pthread_cond_init(&pool->cond, NULL)){
        printf("pthread_cond_init error.\n");
        return NULL;
    }

    for (i = 0; i < pool->threads; i++){
        if(OK != pthread_create(&tid, NULL, thread_pool_cycle, (void *)pool)){
            printf("create thread failed.");
            return NULL;
        }
    }

    return pool;
}

void thread_pool_destroy(thread_pool_t *pool){
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
    free(pool);
}


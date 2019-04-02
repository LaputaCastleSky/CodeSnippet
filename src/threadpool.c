#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "threadpool.h"

void *thread_pool_cycle(void *arg);

void *thread_pool_cycle(void *arg){
    thread_pool_t *pool = (thread_pool_t *)arg;
    thread_task_t *task = NULL;

    for(;;){
        pthread_mutex_lock(&pool->mutex);

        while(pool->head == NULL){
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }

        task = pool->head;
        pool->head = pool->head->next;

        task->handle(task->arg);

        pthread_mutex_unlock(&pool->mutex);
    }
    return NULL;
}

void thread_pool_task_post(thread_pool_t *pool, thread_task_t *task){
    pthread_mutex_lock(&pool->mutex);

    if(pool->head == NULL){
        pool->head = task;
        pool->tail = task;
    }else{
        pool->tail->next = task;
        pool->tail = task;
    }

    pthread_cond_signal(&pool->cond);

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

    pool->head = NULL;
    pool->tail = NULL;

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    for (i = 0; i < pool->threads; i++){
        if(pthread_create(&tid, NULL, thread_pool_cycle, (void *)pool) != 0){
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


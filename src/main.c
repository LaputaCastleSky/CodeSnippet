#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "threadpool.h"

void daemonize(){
    int fd;
    pid_t pid;

    if((pid = fork()) < 0){    
        perror("fork");
        exit(1);
    }else if(pid != 0){ /*parent*/
        exit(0);
    }
    
    setsid();

    if((fd = open("/dev/null", O_RDWR, 0)) != -1){
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if(fd > STDERR_FILENO){
            close(fd);
        }
    }
    
}

void func1(void *arg){
    printf("this task 1 start.\n");
    sleep(1);
    printf("this task 1 end.\n");
}

void func2(void *arg){
    printf("this task 2 start\n");
    sleep(1);
    printf("this task 2 end\n");
}

void func3(void *arg){
    printf("this task 3 start\n");
    sleep(1);
    printf("this task 3 end\n");
}

int main(void){
    //daemonize();
    thread_pool_t *pool = NULL;
    thread_task_t task1;
    thread_task_t task2;
    thread_task_t task3;
    task1.handle = func1;
    task1.next = NULL;
    task2.handle = func2;
    task2.next = NULL;
    task3.handle = func3;
    task3.next = NULL;
    pool = thread_pool_init(12);
    thread_pool_task_post(pool, &task1);
    thread_pool_task_post(pool, &task2);
    thread_pool_task_post(pool, &task3);
    while(1);
}

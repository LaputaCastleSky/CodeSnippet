#include <stdlib.h>
#include <stdio.h>

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

int main(void){
    daemonize();
    while(1);
}
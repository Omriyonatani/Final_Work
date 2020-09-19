#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int count=0;

// signal handler for SIGINT
void sigInt_handler(int sig){
    count++;
}

// signal handler for SIGUSR1
void sigUSR1_handler(int sig){
    printf("%d\n",count);
    exit(0);
}


int main(int argc, char const *argv[]){
    // wait for the signals
    signal(SIGINT,sigInt_handler);
    signal(SIGUSR1,sigUSR1_handler);
    while(1){
        getchar();
        printf("\n");
    }

}
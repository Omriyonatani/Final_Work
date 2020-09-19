#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[]){
    
    // read from the stdin
    int serverPid=atoi(argv[1]);
    int sigNum=atoi(argv[2]);
    int NumOf=atoi(argv[3]);

    // check the signal number INT/USR1 and send the signal.
    if(sigNum == SIGUSR1){
        for(int i=0; i<NumOf;i++){
            kill(serverPid,SIGUSR1); // SEND SIGUSR1
        }
    }else if(sigNum == SIGINT){
        for(int i=0; i<NumOf;i++){
            kill(serverPid,SIGINT);  //SEND SIGINT
        }
    }else{
        printf("Invalid Signal Number !\n");
    }

    return 0;
    
}
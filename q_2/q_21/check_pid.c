#include "errno.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>


int main(int argc, char const *argv[]){
    
    // read from the stdin the pid and send signal    
    int x=atoi(argv[1]);
    int check = kill(x,0);

    // check if exists / no exists / no permission
    if(errno==ESRCH){
        printf("Process %d does not exist\n",x);
    }else if(errno==EPERM){
        printf("Process %d exists but we have no permission\n",x);
    }else if(check==0){
        printf("Process %d exists\n",x);
    }
    return 0;
}

#define _GNU_SOURCE 
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <time.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

/*
SCHED_OTHER		0
SCHED_FIFO		1
SCHED_RR		2
SCHED_BATCH	    3
SCHED_ISO		4
SCHED_IDLE		5
SCHED_DEADLINE	6
*/

 #define gettid() syscall(__NR_gettid)

 #define SCHED_DEADLINE	6

 /* XXX use the proper syscall numbers */
 #ifdef __x86_64__
 #define __NR_sched_setattr		314
 #define __NR_sched_getattr		315
 #endif

 #ifdef __i386__
 #define __NR_sched_setattr		351
 #define __NR_sched_getattr		352
 #endif

 #ifdef __arm__
 #define __NR_sched_setattr		380
 #define __NR_sched_getattr		381
 #endif

 static volatile int done;

 struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

 int sched_setattr(pid_t pid,const struct sched_attr *attr,unsigned int flags){
	return syscall(__NR_sched_setattr, pid, attr, flags);
 }

 int sched_getattr(pid_t pid,struct sched_attr *attr,unsigned int size,unsigned int flags){
	return syscall(__NR_sched_getattr, pid, attr, size, flags);
 }

void *run_deadline_thread(void *data){
	struct sched_attr attr;
	int ret;
	unsigned int flags = 0;

	printf("deadline thread started [%ld]\n", gettid());

	attr.size = sizeof(attr);
	attr.sched_flags = 0;
	attr.sched_nice = 0;
	attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
	attr.sched_policy = SCHED_DEADLINE;
	attr.sched_runtime = 10 * 1000 * 1000;
	attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

	ret = sched_setattr(0, &attr, flags);
	if (ret < 0) {
		done = 0;
		perror("sched_setattr");
		exit(-1);
	}

	while (!done) {
		sleep(1);
	}

	printf("deadline thread dies [%ld]\n", gettid());
	return NULL;
 }

int run_deadline(){
	pthread_t thread;

	printf("main thread [%ld]\n", gettid());

	pthread_create(&thread, NULL, run_deadline_thread, NULL);

	sleep(10);

	done = 1;
	pthread_join(thread, NULL);

	printf("main dies [%ld]\n", gettid());
	return 0;
}



int main(int argc, char const *argv[]){
	// read the policy, priority from the stdin
    int policy=atoi(argv[1]);
    int priority=atoi(argv[2]);
    
    
    // SCHED_DEADLINE
    if(policy==SCHED_DEADLINE){
        run_deadline();
    }else{ // OTHER SCHED_..
        struct sched_param *param = malloc(sizeof(struct sched_param));
        param->sched_priority=priority;
        sched_setscheduler(0,policy,param);
        while(1){
            sleep(1);
        }
    }

    return 0;
}

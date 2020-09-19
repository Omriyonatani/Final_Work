#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. ANSWER: .bss  */
int primes[] = { 2, 3, 5, 7 };  /* 2. ANSWER: .data */

static int
square(int x)                   /* 3. ANSWER: .text */
{
    int result;                 /* 4. ANSWER: stack */

    result = x * x;
    return result;              /* 5. ANSWER: by EAX Register. */
}

static void
doCalc(int val)                 /* 6. ANSWER: .text */
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. ANSWER: stack */

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /* ANSWER: .text */
{
    static int key = 9973;      /* ANSWER: .data */
    static char mbuf[10240000]; /* ANSWER: .bss  */
    char* p;                    /* ANSWER: stack */


    doCalc(key);

    exit(EXIT_SUCCESS);
}
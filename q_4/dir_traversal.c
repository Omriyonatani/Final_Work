#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){
    // switch case for the type - file / directory.
    switch (typeflag){
    case FTW_F:
        printf("F %ld %s\n", sb->st_ino,&(fpath[ftwbuf->base]));
        break;

    case FTW_D:
        printf("D %ld %s\n", sb->st_ino,&(fpath[ftwbuf->base]));
        break;
    
    default:
        break;
    }

    return 0;
}

int main(int argc, char const *argv[]){
    // read the name from the stdin
    const char* name = argv[1];
    // run nftw with my fn function.
    nftw(name,&fn,1,FTW_PHYS);
    return 0;
}
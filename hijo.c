#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char *argv[]){

    if(argc !=2){
        fprintf(stderr, "Error: numero de argumentos introduicidos erroneo.");
    }

    putchar(argv[1][0]);

    return 0;
}
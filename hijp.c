#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char *argv[]){
    char palabra[1024]="";

    sprintf(palabra,"%s",argv[1]);
    printf("%c\n", palabra[0]);

    return 0;
}
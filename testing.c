#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int main(int argc,char *argv[]){    //numero de argumentos y puntero con valor de argumentos 

char size[1024];

sprintf(size, "%s", argv[1]);

char simbol;

//sprintf(simbol,"%c",size[0]);
simbol=size[0];
printf("size[1] %s \n",&size[1]);
printf("size[2] %s \n",&size[2]);
printf("size[3] %s \n",&size[3]);
printf("size[-1] %s \n",&size[-1]);

int tamanio = atoi(size);

if (simbol=="-"){
    printf("menorque");
    tamanio=tamanio*-1;
}
else if (simbol=="+"){
    printf("mayorque");
}else{
    printf("iguala");
}


printf("%d\n",tamanio);

return 0;
}
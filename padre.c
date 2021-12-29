#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<wait.h>

#define MAX_HIJOS   128

int currSize = 0;

pid_t hijos[MAX_HIJOS];

void Manejador ( int num){
    int i;
    printf("Recibida la señal de interrupcion.\n");
    for(i=0; i<currSize; i++){
        printf("El proceso hijo %d es terminado por su padre\n",hijos[i]);
        kill(hijos[i], SIGTERM);
    }
    exit(EXIT_SUCCESS);
}


int main (int argc , char *argv[]){
    int fd[2];
    int i;

    if(pipe(fd)!=0){
        fprintf(stderr,"Error en la creacion de la tuberia.");
        return EXIT_FAILURE;
    }

    if (signal (SIGINT, Manejador ) == SIG_ERR) {
        fprintf(stderr," Error en la manipulación de la señal \n" ) ;
        return EXIT_FAILURE ;
    }



    for (i=1;i<argc; i++){
        switch(hijos[i-1]=fork()){
            case 0:

                close(1);
                if(dup(fd[1])!=1){
                    fprintf(stderr,"Error en la creacion del descriptor de escritura\n");
                    return EXIT_FAILURE;
                }
                
                execl("./hijo","./hijo",argv[i],NULL);
                fprintf(stderr,"Error en la ejecucion del hijo.\n");
                return EXIT_FAILURE;

            case -1:
                fprintf(stderr,"Error en la creacion del hijo.\n");
                return EXIT_FAILURE;

            default:
                currSize++;
                break;

        }
    }


    char msg;

    int pid;
    for (int i=1;i<argc; i++){
        pid=wait(NULL);
        read(fd[0], &msg, sizeof(msg));
        printf("Fin del hijo: <%c>\n",msg);
          
    }

return 0; 
    
}  
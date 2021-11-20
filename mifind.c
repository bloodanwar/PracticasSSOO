#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>    //libreria para declarar variables en bool

#define PATH_MAX 4096    //Tamanio maximo del camino a un nodo

//FUNCION PRINCIPAL
int main(int argc,char *argv[]){    //numero de argumentos y puntero con valor de argumentos 
//DECLARACIÓN DE VARIABLES
int DEPTH=0, ENCONTRADOS=0;
bool BOOL= TRUE;

//MENU DE OPCIONES
for(int i=0; i<argc; i++){  //recorre desde la primera posición hasta el número de argumentos indicado, éste aumenta
        switch(argv[i]) {   //menú que depende de la posición de la línea de arguemtnos 
            case '-maxdepth':
                int MAXDEPTH;
                if(BOOL ==TRUE ){   //función seguida varias veces sin argumento tambien es un error 
                        puts("<<<ERROR>>>\nEn este comando no es posible posicionar dos argumentos seguidos");
                    return 1;
                }
                BOOL=FALSE;
                MAXDEPTH=atoi (argv[i+1]);  //i es la opcion i+1 es el acompañante del argumento
                }
            break;  
            case '-type':
                char TYPE=argv[i+1];
                BOOL=TRUE;
            break;
            case '-name':
                char NAME=argv[i+1];
                BOOL=TRUE;
            break;
            case '-size':
                char SIZE=argv[i+1];
                BOOL=TRUE;
            break;
            default: 
            if(BOOL != TRUE){   //si es falso saltará un error de funcion mal nombrada 
                puts("<<<ERROR>>>\nLa llamada a la funcion no es correcta.\nEl metodo correcto de uso es:mifind <ruta><opciones> \n\n");
                return 1;        
            }else{
                BOOL=FALSE; //no dejamos continuar el programa y establecemos en la siguiente iteración el error
            }
        }  
    }

int contador=0; //contador inicializado a 0

int busqueda(const char *dir, int maxDepth, char type, char size, char name, int currDepth){    //recibe parametros necesarios tales como maximaprofundidad, tipo, nombre, profundiad actual
    //DECLARACION DE VARIABLES
    DIR *d;
    int encontrados=0;
    struct dirent *item, stat st;
    char nombre[PATH_MAX +1];
    bool showReg=FALSE, showDir=FALSE, showSize=FALSE, showName=FALSE;
  
    //INSTRUCCIONES
    
    //Type
    if(type==NULL){ //estudiamos todos los posibles valores que puede obtener esta variable
        showReg=TRUE;
        showDir=TRUE;
    }else if(type=='d'){
        showDir=TRUE;
    }else if(type=='f'){
        showReg=TRUE;
    }else{
        printf("<<<ERROR>>> El comando -type esta mal escrito");    
    }
    if ((d=opendir(dir))==NULL){
        fprintf(stderr, "<<<ERROR>>> en la apertura del directorio %s\n ", dir);
        return;
    }
    
    while ((item=readdir(d))!=NULL){
        if(strcmp(item->d_name,".")==0 || strcmp(item->d_name, "..")==0) continue;  //evvitamos problemas con los directorios . y .. porque hacen bucles infinitos.
        if(size==NULL){
            showSize=TRUE;
        }else if(getchar(size)=='+'){
            if(st.st_size  '-'){
                //SIN TERMINAR (ta saltando el error)
            }
        }

        //Nombre
        if(name==NULL){ //estudiamos todos los posiles valores que puede obtener esta variable
            showName=TRUE;
        }else if(strcmp(item->d_name,name)==0){ 
            showName=TRUE;
        }else {
            printf("<<<ERROR>>>El comando -name no esta mal escrito");
        }

        if(S_ISREG(st.st_mode))&&(showReg==TRUE)&&(showSize==TRUE)&&(showName==TRUE){   //si es un fichero regular a la vez que que el tamano, el nombre o la muestra de ficheros regulares sea verdadera entonces: 
            encontrados++;
            printf(item->d_name);   //mostrar contenido correspondiente->ficheros regulares
        }   
        if(S_ISDIR(st.st_mode)){    //si es un directorio
            if(showDir==TRUE)&&(showSize==TRUE)&&(showName==TRUE){
                encontrados++;
                printf(item->d_name);   //mostrar el contenido correspondiente-> directorios
            }
            if(maxdepth!=currDepth){    //si la profundidad maxima no es la misma que la profundidad actual
                encontrados+=busqueda(nombre,maxDepth, type, size, name, currDepth+1); //si es un directorio realizamos recursividad
            }    
        } 
    }
    closedir(d);
    return encontrados; //devuelve la cantidad de elementos encontrados
}   //fin del metodo "busqueda"
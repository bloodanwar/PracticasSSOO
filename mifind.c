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
bool errLin= true;
int maxdpth;
char type[1024];
char name[1024];
char size[1024];
int checking=0;

//MENU DE OPCIONES
for(int i=0; i<argc; i++){  //recorre desde la primera posición hasta el número de argumentos indicado, éste aumenta


if(strcmp(argv[i],"-maxdepth")==0){   //menú que depende de la posición de la línea de arguemtnos 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
    maxdpth=atoi (argv[i+1]);  //i es la opcion i+1 es el acompañante del argumento
    printf("maxdepth = %d\n",maxdpth);
}else
if(strcmp(argv[i],"-type")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(type,"%s",argv[i+1]);
        printf("Type = %s\n",type);
}else
if(strcmp(argv[i],"-name")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(name,"%s",argv[i+1]);
        printf("name = %s\n",name);    
}else
if(strcmp(argv[i],"-size")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(size,"%s",argv[i+1]);
        printf("Size = %s\n",size);
}
else
    if (errLin==false){

    }
}
return 0;
}
int contador=0; //contador inicializado a 0
//BUSQUEDA RECURSIVA
int busqueda(const char *dir, int maxDepth, char type, char size, char name, int currDepth){    //recibe parametros necesarios tales como maximaprofundidad, tipo, nombre, profundiad actual
    //DECLARACION DE VARIABLES
    DIR *d;
    int encontrados=0;
    struct dirent *item;
    struct stat st;
    char nombre[PATH_MAX +1];
    bool showReg=false, showDir=false, showSize=false, showName=false;
  
    //INSTRUCCIONES
    
    //Type
    if(type==NULL){ //estudiamos todos los posibles valores que puede obtener esta variable
        showReg=true;
        showDir=true;
    }else if(type=='d'){
        showDir=true;
    }else if(type=='f'){
        showReg=true;
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
            showSize=true;
        }else if(getchar(size)=='+'){
            if(st.st_size  '-'){
                //SIN TERMINAR (ta saltando el error)
            }
        }

        //Nombre
        if(name==NULL){ //estudiamos todos los posiles valores que puede obtener esta variable
            showName=true;
        }else if(strcmp(item->d_name,name)==0){ 
            showName=true;
        }else {
            printf("<<<ERROR>>>El comando -name no esta mal escrito");
        }

        if(S_ISREG(st.st_mode)&&(showReg==true)&&(showSize==true)&&(showName==true)){   //si es un fichero regular a la vez que que el tamano, el nombre o la muestra de ficheros regulares sea verdadera entonces: 
            encontrados++;
            printf(item->d_name);   //mostrar contenido correspondiente->ficheros regulares
        }   
        if(S_ISDIR(st.st_mode)){    //si es un directorio
            if((showDir==true)&&(showSize==true)&&(showName==true)){
                encontrados++;
                printf(item->d_name);   //mostrar el contenido correspondiente-> directorios
            }
            if(maxepth!=currDepth){    //si la profundidad maxima no es la misma que la profundidad actual
                encontrados+=busqueda(nombre,maxDepth, type, size, name, currDepth+1); //si es un directorio realizamos recursividad
            }    
        } 
    }
    closedir(d);
    return encontrados; //devuelve la cantidad de elementos encontrados
}   //fin del metodo "busqueda"
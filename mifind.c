#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>    //libreria para declarar variables en bool

#define PATH_MAX 4096    //Tamanio maximo del camino a un nodo

int error(int problema){
    switch(problema){
        case 1:
             printf("<<<ERROR>>> El comando -type esta mal escrito");
            break;
        case 2:
            printf("<<<ERROR>>>error <-option> seguidos.");
            break;
        case 3:
            printf("<<<ERROR>>> el comando -size está mal escrito");
        break;
    }
    return problema;
}

//BUSQUEDA RECURSIVA
int busqueda(const char *dir, int maxDepth, char type[], char size[], char name[], int currDepth){    //recibe parametros necesarios tales como maximaprofundidad, tipo, nombre, profundiad actual
    //DECLARACION DE VARIABLES
    DIR *d;
    int encontrados=0,tamanio;
    struct dirent *item;
    struct stat st;
    char nombre[PATH_MAX +1];
    
    if((d=opendir(dir))==NULL){
        fprintf(stderr, "<<<ERROR>>> en la apertura del directorio %s\n ", dir);
        exit(EXIT_FAILURE);
    }
    
    while ((item=readdir(d))!=NULL){
        if(strcmp(item->d_name,".")==0 || strcmp(item->d_name, "..")==0) continue;  //evitamos problemas con los directorios . y .. porque hacen bucles infinitos.
            sprintf(nombre,"%s/%s",dir,item->d_name);
        if(stat(nombre,&st)==1){
            fprintf(stderr,"Error en la apertura de %s \n",item->d_name);
            exit(EXIT_FAILURE);
        }
        
        bool showReg=false, showDir=false, showSize=false, showName=false;
        //INSTRUCCIONES
        //TYPE
        if(strcmp(type,"")==0){ //estudiamos todos los posibles valores que puede obtener esta variable
            showReg=true;
            showDir=true;        
        }
        else if(strcmp(type,"d")==0){
            showDir=true;
        }else if(strcmp(type,"f")==0){
            showReg=true;
        }else{
        error(1);   
        }
        //NAME
        if(strcmp(name,"")==0){ //estudiamos todos los posiles valores que puede obtener esta variable
            showName=true;
        }else if(strcmp(item->d_name,name)==0){ 
            showName=true;
        }else {
            showName=false;
        }

        //SIZE 
        if(strcmp(size,"")==0){
            showSize=true;
        }
        else{    
            char simbol;
            int numero;
            simbol=size[0];
            numero=(atoi(&size[1]));

            if (simbol=='-'){
                if(st.st_size < numero){
                    showSize=true;
                }
            }
            else if (simbol=='+'){
                if(st.st_size > numero){
                    showSize=true;
                }
            }
            else{
                numero=(atoi(&size[0]));
                if(st.st_size==numero){
                    showSize=true;
                }
            }
        }
        if(S_ISREG(st.st_mode)&&(showReg==true)&&(showSize==true)&&(showName==true)){   //si es un fichero regular a la vez que que el tamano, el nombre o la muestra de ficheros regulares sea verdadera entonces: 
            encontrados++;
            printf("%s con tamanio %ld\n",item->d_name,st.st_size);   //mostrar contenido correspondiente->ficheros regulares
        }   
        if(S_ISDIR(st.st_mode)){    //si es un directorio
            if((showDir==true)&&(showSize==true)&&(showName==true)){
                encontrados++;
                showSize=false;
                printf("%s con tamanio %ld\n",item->d_name,st.st_size);   //mostrar el contenido correspondiente-> directorios
            }
            if(maxDepth!=currDepth){    //si la profundidad maxima no es la misma que la profundidad actual
                showSize=false;
                encontrados+=busqueda(nombre,maxDepth, type, size, name, currDepth+1); //si es un directorio realizamos recursividad
            }    
        } 
    }

    closedir(d);
    return encontrados; //devuelve la cantidad de elementos encontrados
}   //fin del metodo "busqueda"


//FUNCION PRINCIPAL
int main(int argc,char *argv[]){    //numero de argumentos y puntero con valor de argumentos 

//DECLARACIÓN DE VARIABLES
int DEPTH=0, ENCONTRADOS=0;
bool errLin= false;
int maxdpth;
char type[1024]="";
char name[1024]="";
char size[1024]="";
char ruta[1024]=".";
int checking=0;

//MENU DE OPCIONES
for(int i=1; i<argc; i++){  //recorre desde la primera posición hasta el número de argumentos indicado, éste aumenta
    if(strcmp(argv[i],"-maxdepth")==0){   //menú que depende de la posición de la línea de arguemtnos 
        if(errLin==true){
            error(2);
        }
    maxdpth=atoi (argv[i+1]);  //i es la opcion i+1 es el acompañante del argumento
    printf("maxdepth = %d\n",maxdpth);
    errLin=true;
    }else if(strcmp(argv[i],"-type")==0){ 
        if(errLin==true){
            error(2);
        }
        sprintf(type,"%s",argv[i+1]);
        printf("Type = %s\n",type);
        errLin = true;
    }else if(strcmp(argv[i],"-name")==0){ 
    if(errLin==true){
        error(2);
    }
        sprintf(name,"%s",argv[i+1]);
        printf("name = %s\n",name); 
        errLin = true;   
    }else if(strcmp(argv[i],"-size")==0){ 
        if(errLin==true){
            error(2);
        }
        sprintf(size,"%s",argv[i+1]);
        printf("Size = %s\n",size);
        errLin=true;
    }else if (errLin==false){
        if(strcmp(argv[1],argv[i])==0){
            sprintf(ruta,"%s",argv[i]);
        }else{
            printf("<<<ERROR>>>\nLa llamada a la funcion no es correcta.\nEl metodo correcto de uso es: mifind <ruta><opciones> \n \n");
        }
    }else {
        errLin=false;
    }
}

int encontrados=0;

printf("------------------\n");
encontrados=busqueda(ruta,maxdpth,type,size,name,0);
printf("\nSe han encontrado %d archivos\n",encontrados);
return 0;
}
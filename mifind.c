#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>    //libreria para declarar variables en bool

#define PATH_MAX 4096    //Tamanio maximo del camino a un nodo

//BUSQUEDA RECURSIVA
int busqueda(const char *dir, int maxDepth, char type[], char size[], char name[], int currDepth){    //recibe parametros necesarios tales como maximaprofundidad, tipo, nombre, profundiad actual
    //DECLARACION DE VARIABLES

    DIR *d;
    int encontrados=0;
    struct dirent *item;
    struct stat st;
    char nombre[PATH_MAX +1];
    bool showReg=false, showDir=false, showSize=false, showName=false;
  
    //INSTRUCCIONES
    
    //Type
    if(strcmp(type,"")==0){ //estudiamos todos los posibles valores que puede obtener esta variable
        showReg=true;
        showDir=true;        
    }
    else if(strcmp(type,"d")==0){
        showDir=true;
    }else if(strcmp(type,"f")==0){
        showReg=true;
    }else{
        printf("<<<ERROR>>> El comando -type esta mal escrito");    
    }

    if((d=opendir(dir))==NULL){
        fprintf(stderr, "<<<ERROR>>> en la apertura del directorio %s\n ", dir);
        return ;
    }
    
    while ((item=readdir(d))!=NULL){
        if(strcmp(item->d_name,".")==0 || strcmp(item->d_name, "..")==0) continue;  //evitamos problemas con los directorios . y .. porque hacen bucles infinitos.
        
    
        sprintf(nombre,"%s/%s",dir,item->d_name);
        if(stat(nombre,&st)==1){
            fprintf(stderr,"Error en la apertura de %s \n",item->d_name);
            return;
        }
        
        //Size
        showSize=true;
    
        //Nombre
        if(strcmp(name,"")==0){ //estudiamos todos los posiles valores que puede obtener esta variable
            showName=true;
        }else if(strcmp(item->d_name,name)==0){ 
            showName=true;
        }else {
            showName=false;
        }
        if(S_ISREG(st.st_mode)&&(showReg==true)&&(showSize==true)&&(showName==true)){   //si es un fichero regular a la vez que que el tamano, el nombre o la muestra de ficheros regulares sea verdadera entonces: 
            encontrados++;
            printf("%s\n",item->d_name);   //mostrar contenido correspondiente->ficheros regulares
        }   
        if(S_ISDIR(st.st_mode)){    //si es un directorio
            if((showDir==true)&&(showSize==true)&&(showName==true)){
                encontrados++;
                printf("%s\n",item->d_name);   //mostrar el contenido correspondiente-> directorios
            }
            if(maxDepth!=currDepth){    //si la profundidad maxima no es la misma que la profundidad actual
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
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
    maxdpth=atoi (argv[i+1]);  //i es la opcion i+1 es el acompañante del argumento
    printf("maxdepth = %d\n",maxdpth);
    errLin=true;
}else
if(strcmp(argv[i],"-type")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(type,"%s",argv[i+1]);
        printf("Type = %s\n",type);
        errLin = true;
}else
if(strcmp(argv[i],"-name")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(name,"%s",argv[i+1]);
        printf("name = %s\n",name); 
        errLin = true;   
}else
if(strcmp(argv[i],"-size")==0){ 
    if(errLin==true){
        printf("<<<ERROR>>>error <-option> seguidos.");
    }
        sprintf(size,"%s",argv[i+1]);
        printf("Size = %s\n",size);
        errLin=true;
}else
    if (errLin==false){
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
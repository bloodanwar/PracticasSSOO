#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PATH_MAX 4096 //Tamanio maximo del camino a un nodo



int main ( int argc , char* argv[] ){
    int maxDepth=-1;
    char type = NULL;
    char size = NULL;
    char name = NULL;


    bool errCeck=true;
/* Tratamiento de la linea de ordenes*/
for(int i=0; i<argc;i++){
    switch (argv[i]){
    case '-maxdepth':
            continue;
    break;  

    default:
    if (errCheck==true){
        continue;
    }
    
    break;
    }


}
if(argv[1]==NULL){
    busqueda(".", maxDepth, type, size, name, 0) ;
}else busqueda(argv[1], maxDepth, type, size, name, 0);
printf("%d\n",contador);

return EXIT_SUCCESS;
}

int contador=0;

int busqueda(const char *dir, int maxDepth, char type, char size, char name, int currDepth){
    DIR *d;
    int encontrados=0;
    struct dirent *item;
    char nombre[PATH_MAX +1];
    struct stat st;
    bool showReg=FALSE, showDir=FALSE, showSize=FALSE, showName=FALSE;
  
    if(type==NULL){
        showReg=TRUE;
        showDir=TRUE;
    }else if(type=='d'){
        showDir=TRUE;
    }else if(type=='f'){
        showReg=TRUE;
    }else{
        printf("<<<Error>>> El comando -type esta mal escrito");
    }
    if ((d=opendir(dir))==NULL){
        fprintf(stderr, "Error en la apertura del directorio %s\n ", dir);
        return;
    }
    
    while ((item=readdir(d))!=NULL){
        if(strcmp(item->d_name,".")==0 || strcmp(item->d_name, "..")==0) continue;  //evvitamos problemas con los directorios . y .. porque hacen bucles infinitos.
        if(size==NULL){
            showSize=TRUE;
        }else if(getchar(size)=='+'){
            if(st.st_size > )
        }

        if(name==NULL){
            showName=TRUE;
        }else if(strcmp(item->d_name,name)==0){
            showName=TRUE;
        }else {
            printf("ERROR");
        }

        if(S_ISREG(st.st_mode))&&(showReg==TRUE)&&(showSize==TRUE)&&(showName==TRUE){ 
            encontrados++;
            printf(item->d_name);
        }
        if(S_ISDIR(st.st_mode)){
            if(showDir==TRUE)&&(showSize==TRUE)&&(showName==TRUE){
                encontrados++;
                printf(item->d_name);
            }
            if(maxdepth!=currDepth){
                encontrados+=busqueda(nombre,maxDepth, type, size, name, currDepth+1); //si es un directorio realizamos recursividad
            }    
        } 
    }
    closedir(d);
    return encontrados;
}
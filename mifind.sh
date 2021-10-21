#!/bin/bash

function error (){
printf "!!!!!!!!!!\n"
printf "ERROR! Error en la llamada a la funcion. \nEl metodo correcto es: "
echo    "mifind 'ruta' <opciones>"
exit -1
}

function busqueda (){
    if [ ! -z $TIPO ]; then
        printf "tipo $TIPO\n"
    fi
    if [ ! -z $MAXDEPTH ]; then
        printf "Profundidad maxima de $MAXDEPTH\n"
    fi
    if [ ! -z $RUTA ]; then
        printf "Ruta a seguir $RUTA\n"
    fi
}

CHECKER=1
for i in $@ ; do
case $i in
    "-maxdepth"|"-type")
        OPCION=$i
        CHECKER=1
        ;;
    *)
        if [ $CHECKER -ne 0 ]; then
            case $OPCION in 
                "-maxdepth")
                    MAXDEPTH=$i
                    ;;
                "-type")
                    TIPO=$i
                    ;;
                "")
                    if [ $i != $1 ] ; then
                        error
                    else
                        RUTA=$i
                    fi
                    ;;
            esac
            CHECKER=$((CHECKER - 1))
        else
            error
        fi
esac
done
busqueda
exit 0

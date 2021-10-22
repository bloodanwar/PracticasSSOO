#!/bin/bash

function error (){
printf "!!!!!!!!!!\n"
printf "ERROR! Error en la llamada a la funcion. \nEl metodo correcto es: "
echo    "mifind 'ruta' <opciones>"
exit -1
}

function busqueda (){
    if [ ! -z $MAXDEPTH ]; then
        DEPTH=$MAXDEPTH
    fi
    if [ ! -z $RUTA ]; then
        RUTA=.
    fi

    case $TIPO in 
        "d")
            printf "Busca directorios\n"
            ;;
        "f")
            printf "Busca archivos \n"
            ;;
        *)
            printf "Busca todo \n"
            ;;
    esac
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

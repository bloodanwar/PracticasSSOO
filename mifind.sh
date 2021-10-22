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
    for rute in $1/* ; do
        case $TIPO in 
            "d")
                if [ -d "$rute" ]; then
                    echo $rute
                fi
                ;;
            "f")
                if [ -f "$rute" ]; then
                    echo $rute
                fi
                ;;
            *)
                    echo $rute
            ;;
        esac
        #recursibidad
        if [ -d "$rute" ] ; then 
            busqueda "$rute"
        fi 
    done
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
if [ -z $RUTA ]; then
    RUTA="."
fi
if [ ! -d "$RUTA" ]; then
    error
fi
busqueda "$RUTA"
exit 0

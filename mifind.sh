#!/bin/bash

function busqueda (){
    if [ ! -z $MAXDEPTH ]; then
        DEPTH=$MAXDEPTH
    fi
    for rute in $1/* ; do
        #comprobacion del -type
        if [ "$TIPO" == "d" ]
        then
            if [ -d "$rute" ]; then
                echo $rute
            fi
        elif [ "$TIPO" == "f" ]
        then
            if [ -f "$rute" ]; then
                echo $rute
            fi
        elif [ -z $TIPO ]
        then
            echo $rute
        else 
            printf "<<<ERROR>>>\nEl '-type' seleccionado no existe. Solo se permiten 'd' o 'f'\n \n"
            exit -1
        fi

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
                        printf "<<<ERROR>>>\nLa llamada a la funcion no es correcta.\nEl metodo correcto de uso es: mifind <ruta><opciones> \n \n"
                        exit -1
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
    printf "\n<<<ERROR>>>\nLa ruta especificada para la busqueda no es un directorio.\nEl metodo correcto de uso es: mifind <ruta><opciones> \n \n"
    exit -1
fi
busqueda "$RUTA"
exit 0

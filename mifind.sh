#!/bin/bash
function busqueda (){
    for rute in $1/* ; do
        #comprobacion del -type
        if [ "$TIPO" == "d" ]
        then
            if [ -d "$rute" ]; then
                echo $rute
                ENCONTRADOS=$((ENCONTRADOS + 1))
            fi
        elif [ "$TIPO" == "f" ]
        then
            if [ -f "$rute" ]; then
                echo $rute
                ENCONTRADOS=$((ENCONTRADOS + 1))
            fi
        elif [ -z $TIPO ]
        then
            echo $rute
            ENCONTRADOS=$((ENCONTRADOS + 1))
        else 
            printf "<<<ERROR>>>\nEl '-type' seleccionado no existe. Solo se permiten 'd' o 'f'\n \n"
            exit -1
        fi
        #recursibidad y comprobacion del maxdepth
        if [ -d "$rute" ] && [ "$DEPTH" != "$MAXDEPTH" ] ; then 
            DEPTH=$((DEPTH + 1))
            busqueda "$rute"
            DEPTH=$((DEPTH - 1))
        fi 
    done
}
#inicializacion de las variables.
BOOL=1
DEPTH=0
ENCONTRADOS=0
for i in $@ ; do
case $i in
    "-maxdepth"|"-type")
        OPCION=$i
        BOOL=1
        ;;
    *)
        if [ $BOOL -ne 0 ]; then
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
            BOOL=$((BOOL - 1))
        else
            printf "<<<ERROR>>>\nLa llamada a la funcion no es correcta.\nEl metodo correcto de uso es: mifind <ruta><opciones> \n \n"
            exit -1
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
printf "\nSe han encontrado $ENCONTRADOS elementos.\n\n"
exit 0
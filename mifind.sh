#!/bin/bash

function error (){
printf "!!!!!!!!!!\n"
printf "ERROR! Error en la llamada a la funcion. \nEl metodo correcto es: "
echo    "mifind 'ruta' <opciones>"
exit -1
}
COUNTER=1
for i in $@ ; do
case $i in
    "-maxdepth"|"-type")
        OPCION=$i
        COUNTER=1
        ;;

    *)
        if [ ! -z $COUNTER ]; then
            case $OPCION in 
                "-maxdepth")
                    echo "profundidad maxima $i"
                    ;;

                "-type")
                    echo "tipo $i"
                    ;;

                "")
                    if [ $i != $1 ] ; then
                        error
                    else
                        echo "ruta: $i"
                    fi
                    ;;
            esac
            COUNTER=($COUNTER - 1)
        else
            error
        fi
esac
done
exit 0

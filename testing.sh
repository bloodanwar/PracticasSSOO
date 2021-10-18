#!/bin/bash
if [ $# -lt 3]
then
    echo "El comando esta mal escrito. El modo correcto es mifind <camino> -opciones"
    exit -1
fi
if [ -z $((# % 2))]
then	
    echo "Num args es par"
else
    echo "Num args es impar."
fi  
exit 0
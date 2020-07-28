#!/bin/bash
if [ $# -ne 1 ]; 
    then echo "input macro name "
    exit 1;
fi
MACRO=$1
export projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/baconSim
echo "salloc --qos=interactive -C haswell -n 1"
echo "shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/MaGe $projectdir/$MACRO"
#salloc --qos=interactive -C haswell -n 1
shifter --env-file=$projectdir/MaGeEnvirons --image docker:legendexp/legend-base:latest $projectdir/bin/Linux-g++/MaGe $projectdir/$MACRO

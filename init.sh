#!/bin/bash
alias dds='ls --color -alsF'
export SHIFTER=/global/project/projectdirs/m2676/users/mgold/shifter
export PATH=./:$PATH
export G4WORKDIR=/global/project/projectdirs/m2676/users/mgold/shifter/baconSim
source $G4WORKDIR/setup.sh
source $SHIFTER/rootsetup.sh
echo $SHIFTER
echo $PATH

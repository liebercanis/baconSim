#!/bin/bash
alias dds='ls --color -alsF'
export SHIFTER=/global/project/projectdirs/m2676/users/mgold/shifter
export G4WORKDIR=/global/project/projectdirs/m2676/users/mgold/shifter/baconSim
export MGDODIR=/global/project/projectdirs/m2676/users/mgold/shifter/MGDO
export PATH=./:$PATH
source $SHIFTER/rootsetup.sh
echo $SHIFTER
echo $PATH
echo "./configure  --disable-g4gdml --enable-streamers --with-rootsys=$ROOTSYS --with-mgdo=$MGDODIR --prefix=$G4WORKDIR --exec-prefix=$G4WORKDIR"

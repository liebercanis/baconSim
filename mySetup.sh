#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$G4WORKDIR/lib
source setup.sh
export PATH=$BACONSIM/bin/Linux-g++:$PATH
printenv LD_LIBRARY_PATH

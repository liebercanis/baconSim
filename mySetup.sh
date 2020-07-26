#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$G4WORKDIR/lib
source setup.sh
printenv LD_LIBRARY_PATH

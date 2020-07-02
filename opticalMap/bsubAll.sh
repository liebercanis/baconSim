#!/bin/bash
FIRST=0
LAST=1
read -p 'Start Run Number: ' FIRST
read -p 'Stop Run Number: ' LAST
for a in `seq $FIRST $LAST` ; do  
  echo "sbatch sbatchMap$a.sh "
  sbatch sbatchMap$a.sh
done

#!/bin/bash 
if [ $# -ne 2 ]; 
    then echo "input start and stop run numbers";
      exit 0
fi

echo from $1 to $2
i=$1
while [[ $i -le $2 ]]
  do
    echo sbatch sbatchBacon$i.sh
    sbatch sbatchBacon$i.sh
    ((i = i + 1))
done


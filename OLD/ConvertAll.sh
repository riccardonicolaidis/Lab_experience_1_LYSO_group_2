#!/bin/bash                                                                     

if [ $# -lt 2 ]
  then
      echo "usage: ./ConvertAll.sh FirstRUNID LastRUNID"
      exit
fi

for inum in $(seq $1 $2)
do
    echo "producing" $inum "DST"
    rm ../DATA/testlyso$inum.dst
    mv ../DATA/testlyso$inum/Autosave/* ../DATA/testlyso$inum/.
    source mergefile.sh ../DATA/testlyso$inum $inum
done

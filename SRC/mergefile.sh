#!/bin/bash 

if [ $# -lt 2 ]
  then
      echo "usage: ./mergefile.sh ../DATA/DIRNAME RUNID"
      exit
fi

# ./mergefile testlysofolderNN NN 
rm -rf $1.dst  
touch $1.dst
echo "producing" ../DST/$1.dst
conta=0
for iname in $1/*.txt 
do
    num=$(($2*10000+$conta))
   
    val=$( cat $iname | grep value | sed 's/value/'"$num"'/g' )
    if [[ $val =~ .*inar.* ]]
    then
	echo $num "broken"
    else
	echo $val >> $1.dst
    fi
conta=$((conta+1))
done

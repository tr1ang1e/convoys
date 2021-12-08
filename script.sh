#!/bin/bash

echo "echo script"

var=0
if (( var < 10 ))
then 
    echo "if";
elif [ $var -eq 11 ]
then
    echo "11"
else
    echo "else"
fi

for (( i = 0; i < 10; ++i ))
do
    echo "$i"
done

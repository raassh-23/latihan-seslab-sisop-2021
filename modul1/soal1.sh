#!/bin/bash

let arg=$#%2
if [ $arg == 0 ]
then
    echo "Anda belum beruntung, coba lagi."
else
    sum=0
    for i in $*
    do
	let sum=$sum+$i
    done
    echo $sum
fi

#!/bin/bash

LC_NUMERIC=C
awk -F , '$5 ~ /Iris-setosa/ && $1 > 5.4 {printf "Luas petal pada baris %d adalah %.2f\n", NR, ($3 * $4)}' iris.data

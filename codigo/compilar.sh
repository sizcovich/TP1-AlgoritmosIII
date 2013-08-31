#!/bin/sh

g++ -o ./ej1/ej1 ./ej1/ej1.cpp
# g++ -o ./ej2/ej2 ./ej2/ej2.cpp
# g++ -std=c++0x -o ./ej3/ej3 ./ej3/ej3.cpp

cat ./ej1/ej1.in | ./ej1/ej1 #1> ./ej1/ej1.out 2> ./ej1/ej1.dat
# cat ./ej2/ej2.in | ./ej2/ej2 #1> ./ej2/ej2.out 2> ./ej2/ej2.dat
# cat ./ej3/ej3.in | ./ej3/ej3 1> ./ej3/ej3.out 2> ./ej3/ej3.dat

#!/bin/sh
mkdir extra
g++ -c main.cpp -o extra/main.o
g++ -c lodepng.cpp -o extra/lodepng.o
g++ extra/main.o extra/lodepng.o -lGL -lGLU -lglut
rm -rf extra
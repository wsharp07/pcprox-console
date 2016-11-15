#!/bin/bash
mkdir -p build
g++ -c -g -Wall -I./lib/pcProxAPI/ -I./lib/hidapi/ main.cpp  -o pcprox-console.o
g++ -o build/pcprox-console  pcprox-console.o -lpcProxAPI -lhidapi-hidraw -L./lib/pcProxAPI/ -L./lib/hidapi/
rm pcprox-console.o
strip build/pcprox-console

#!/bin/bash
mkdir -p build
mkdir -p bin
g++ -c -g -Wall -I./lib/pcProxAPI/ -I./lib/hidapi/ src/main.cpp  -o bin/pcprox-console.o
g++ -c -g -Wall -I./lib/pcProxAPI/ -I./lib/hidapi/ src/pcprox.cpp  -o bin/pcprox.o
g++ -c -g -Wall src/syslogger.cpp -o bin/syslogger.o
g++ -o build/pcprox-console  bin/pcprox-console.o bin/syslogger.o bin/pcprox.o -lpcProxAPI -lhidapi-hidraw -L./lib/pcProxAPI/ -L./lib/hidapi/
rm bin/pcprox-console.o
rm bin/syslogger.o
rm bin/pcprox.o
strip build/pcprox-console

#!/bin/bash
mkdir -p build
g++ -c -g -Wall -I./lib/pcProxAPI/ -I./lib/hidapi/ main.cpp  -o pcprox-console.o
g++ -c -g -Wall -I./lib/pcProxAPI/ -I./lib/hidapi/ pcprox.cpp  -o pcprox.o
g++ -c -g -Wall syslogger.cpp -o syslogger.o
g++ -o build/pcprox-console  pcprox-console.o syslogger.o pcprox.o -lpcProxAPI -lhidapi-hidraw -L./lib/pcProxAPI/ -L./lib/hidapi/
rm pcprox-console.o
rm syslogger.o
strip build/pcprox-console

#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "You need to run as root in order to access the reader"
  exit
fi

./build.sh
export LD_LIBRARY_PATH='./lib/pcProxAPI:./lib/hidapi'
./build/pcprox-console
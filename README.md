# PcProx Console
## Sample app written in C++

## Prerequisites

1. Install libudev0 module

```bash
sudo apt-get install libudev1:i386
sudo ln -sf /lib/x86_64-linux-gnu/libudev.so.1 /lib/x86_64-linux-gnu/libudev.so.0
```

2. Copy `libhidapi-hidraw.so.0.0.0` to the `lib\hidapi` folder

3. Copy `libpcProxAPI.so.7.2.14` to the `lib\pcProxAPI` folder

## Running the app

```bash
sudo ./run.sh
```
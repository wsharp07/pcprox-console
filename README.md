# PcProx Console

A C++ console application for interacting with pcProx card readers. Tested and built on Ubunut 16.04 64-bit.

### Prerequisites

1. Install Build Tools

```bash
sudo apt-get install build-essential
```

2. Install libudev0 module

```bash
sudo apt-get install libudev1:i386 && sudo ln -sf /lib/x86_64-linux-gnu/libudev.so.1 /lib/x86_64-linux-gnu/libudev.so.0
```

3. Copy `libhidapi-hidraw.so.0.0.0` to the `lib\hidapi` folder

4. See the README file in the `lib/pcProxAPI` folder for the files you will need to copy there from the pcProx SDK. More information on the SDK can be found here: https://www.rfideas.com/products/sdk/universal-enroll-sdk

## Running the app

```bash
sudo ./run.sh
```

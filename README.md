# PcProx Console

A C++ console application for interacting with pcProx card readers. Tested and built on Ubuntu 16.04 64-bit.

### Prerequisites

1. Install dependencies

    ```bash
    sudo apt-get install build-essential cmake libhidapi-dev libhidapi-hidraw0 libhidapi-libusb0
    ```

2. See the README file in the `lib/pcProxAPI` folder for the files you will need to copy there from the pcProx SDK. More information on the SDK can be found here: https://www.rfideas.com/products/sdk/universal-enroll-sdk


### Building the app

```bash
./configure && make
```

### Running the app

```bash
sudo ./bin/pcprox-console
```

### Resources

**C++ Core Guidelines**

http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main

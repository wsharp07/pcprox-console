# PcProx Console

A C++ console application for interacting with pcProx card readers. Tested and built on Ubuntu 16.04 64-bit.

### Prerequisites

1. Install Build Tools and libhidapi modules

    ```bash
    sudo apt-get install build-essential libhidapi-dev libhidapi-hidraw0 libhidapi-libusb0
    ```

2. See the README file in the `lib/pcProxAPI` folder for the files you will need to copy there from the pcProx SDK. More information on the SDK can be found here: https://www.rfideas.com/products/sdk/universal-enroll-sdk

### Running the app

```bash
sudo ./run.sh
```

### Resources

**C++ Core Guidelines**

http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#main

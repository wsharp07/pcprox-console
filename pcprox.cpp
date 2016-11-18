#include "string"
#include <stdio.h>
#include "lib/pcProxAPI/pcProxAPI.h"
#include "pcprox.h"

using namespace std;

Pcprox::Pcprox()
{
    is_connected = false;
    number_of_devices = 0;
}

bool Pcprox::connect()
{
    if (this->is_connected) return false;

    bool rc = try_to_connect();
    if (rc)
    {
        number_of_devices = GetDevCnt();
        is_connected = true;
    }

    return number_of_devices > 0;
}

int Pcprox::try_to_connect()
{
    sleep(1);
    USBDisconnect();
    SetDevTypeSrch(PRXDEVTYP_USB);
    return usbConnect();
}

void Pcprox::disconnect()
{
    USBDisconnect();
}

int Pcprox::get_last_lib_err()
{
    return GetLastLibErr();
}

string Pcprox::get_card_id()
{
    BYTE buf[36];

    // Get data from queue and clear
    GetQueuedID(1,1);
    for(short j=0; j<35; j++)
    {
        buf[j] = GetQueuedID_index(j);
    }
    int nBits = buf[32];

    // No data found in queue
    if (nBits == 0) return "";

    // Data found in queue
    unsigned int bytes = (nBits+7)/8;

    return try_get_card_id(bytes,buf);
}

string Pcprox::try_get_card_id(unsigned int bytes, BYTE buf[36])
{
    // 00 00 00 00 00 00
    char buffer[18];
    for(unsigned int i=0; i<bytes; i++)
    {
        sprintf(&buffer[3*i],"%02X ",buf[i] & 255);
    }

    return buffer;
}
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include "lib/pcProxAPI/pcProxAPI.h"

using namespace std;

volatile sig_atomic_t stop;
void inthand(int signum) {
    stop = 1;
}

//
// Show returned CSN from Queued ID function call
//
void ShowQueuedID(short cid, short chold)
{
    BYTE buf[36];
    GetQueuedID(cid,chold);
    for(short j=0; j<35; j++)
    {
        buf[j] = GetQueuedID_index(j);
    }
    int nBits = buf[32];
    int age = buf[33];
    int ovr = buf[34];
    int lot = buf[35];

    unsigned int bytes = (nBits+7)/8;

    printf("GetQueuedID: Age %3d, Ovr %3d, Lock %3d, Bits %3d, Data ",age,ovr,lot,nBits);
    for(unsigned int i=0; i<bytes; i++)
    {
        printf("%02X ",buf[i] & 255);
    }
    printf("\n");
}

//
// Delay N Milliseconds
//
void Delay(int ms)
{
    usleep(ms*1000);
}

int Connect()
{
    sleep(1);
    USBDisconnect();
    SetDevTypeSrch(PRXDEVTYP_USB);
    return usbConnect();
}

int TryToConnect()
{
    int numberOfDevices = 0;
    printf("** Please wait... Trying to connect to reader **\n");
    bool rc = Connect();
    if (rc)
    {
        numberOfDevices = GetDevCnt();
        printf("Number of connected readers: %d\n", numberOfDevices);
        printf("Ready to accept card scan...\n");
    }
    return numberOfDevices;
}

int main() {
    signal(SIGINT, inthand);

    printf("\n###\n");
    printf("Starting the console\n");
    printf("Press CTRL+C to exit\n");
    printf("###\n\n");

    int numberOfDevices = 0;

    while (!stop)
    {
        if (numberOfDevices == 0)
        {
            numberOfDevices = TryToConnect();
        }

        if(numberOfDevices > 0)
        {
            unsigned bytes = 0;
            BYTE buf[40];
            int nBits = GetActiveID(buf,sizeof(buf));
            if(nBits > 0)
            {
                bytes = (nBits+7)/8;
                printf("GetActiveCardID: ....................... Bits %3d, Data ",nBits);
                for(unsigned int i=0; i<bytes; i++)
                {
                    printf("%02X ",buf[i] & 255);
                }
                printf("\n");
                ShowQueuedID(0,0);
            }
            if(nBits == 0 && GetLastLibErr() > 0)
            {
                printf("Lost reader connection\n");
                numberOfDevices = 0;
            }
            Delay(250);
        }
    }
    return 0;
}


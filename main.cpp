#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include "lib/pcProxAPI/pcProxAPI.h"

using namespace std;

volatile sig_atomic_t stop;
void inthand(int signum) {
    stop = 1;
}

void start_logging(const char* filename)
{
    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog (filename, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
}

void stop_logging()
{
    closelog();
}

void log_info(const char* message)
{
    syslog(LOG_NOTICE, "%s", message);
}

void delay(int ms)
{
    usleep(ms*1000);
}

int connect()
{
    sleep(1);
    USBDisconnect();
    SetDevTypeSrch(PRXDEVTYP_USB);
    return usbConnect();
}

int try_to_connect()
{
    int numberOfDevices = 0;
    printf("** Please wait... Trying to connect to reader **\n");
    bool rc = connect();
    if (rc)
    {
        numberOfDevices = GetDevCnt();
        printf("Number of connected readers: %d\n", numberOfDevices);
        printf("Ready to accept card scan...\n");
    }
    return numberOfDevices;
}

string get_card_id(unsigned int bytes, BYTE buf[36])
{
    // 00 00 00 00 00 00
    char buffer[18];
    for(unsigned int i=0; i<bytes; i++)
    {
        sprintf(&buffer[3*i],"%02X ",buf[i] & 255);
    }

    return buffer;
}

void try_get_card_id()
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
    if (nBits == 0) return;

    // Data found in queue
    unsigned int bytes = (nBits+7)/8;

    string card_id = get_card_id(bytes,buf);
    printf("Card Read: %s\n", card_id.c_str());
}

int main(int argc, char *argv[]) {
    start_logging("pcprox-console");
    signal(SIGINT, inthand);

    log_info("Starting the console");

    printf("\n###\n");
    printf("Starting the console\n");
    printf("Press CTRL+C to exit\n");
    printf("###\n\n");

    int numberOfDevices = 0;

    while (!stop)
    {
        if (numberOfDevices == 0)
        {
            numberOfDevices = try_to_connect();
        }

        if(numberOfDevices > 0)
        {
            try_get_card_id();

            if(GetLastLibErr() > 0)
            {
                printf("Lost reader connection\n");
                numberOfDevices = 0;
            }

            delay(250);
        }
    }

    stop_logging();
    return(EXIT_SUCCESS);
}
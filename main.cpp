#include <stdio.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include "lib/pcProxAPI/pcProxAPI.h"
#include "pcprox.h"
#include "syslogger.h"

using namespace std;

volatile sig_atomic_t stop;
void inthand(int signum) {
    stop = 1;
}

void delay(int ms)
{
    usleep(ms*1000);
}

int main(int argc, char *argv[]) {
    Syslogger logger;
    logger.start_logging("pcprox-console");
    signal(SIGINT, inthand);

    logger.info("Starting the console with class");

    printf("\n###\n");
    printf("Starting the console\n");
    printf("Press CTRL+C to exit\n");
    printf("###\n\n");

    bool is_connected = false;
    Pcprox reader;

    while (!stop)
    {
        if (is_connected)
        {
            string card_id = reader.get_card_id();
            if (card_id.empty()) continue;

            printf("Card Read: %s\n", card_id.c_str());

            if(reader.get_last_lib_err() > 0)
            {
                printf("Lost reader connection\n");
                is_connected = false;
            }

            delay(250);
        }
        else
        {
            printf("** Please wait... Trying to connect to reader **\n");
            is_connected = reader.connect();

            if (is_connected)
            {
                printf("Ready to accept card scan...\n");
            }
        }
    }

    logger.stop_logging();
    return(EXIT_SUCCESS);
}
#include "../include/syslogger.h"
#include "syslog.h"

void Syslogger::start_logging(const char* filename)
{
    this->filename = filename;
    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog (this->filename, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
}

void Syslogger::stop_logging()
{
    closelog();
}

void Syslogger::info(const char* message)
{
    syslog(LOG_NOTICE, "%s", message);
}

void Syslogger::warn(const char* message)
{
    syslog(LOG_WARNING, "%s", message);
}

void Syslogger::error(const char* message)
{
    syslog(LOG_ERR, "%s", message);
}
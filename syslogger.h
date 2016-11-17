#pragma once

class Syslogger
{
public:
    void start_logging(const char* filename);
    void stop_logging();
    void info(const char* message);
    void warn(const char* message);
    void error(const char* message);

private:
    const char* filename;
};
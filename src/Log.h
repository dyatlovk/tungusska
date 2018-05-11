#ifndef TUNGUSSKA_LOG_H
#define TUNGUSSKA_LOG_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <chrono>

 enum TLogLevel {ERROR, INFO, DEBUG, FATAL};

class Log 
{

public:

    Log();

    ~Log();

    std::stringstream& Get(TLogLevel level = INFO);

protected:
    std::stringstream ss;

public:
    static TLogLevel& ReportingLevel();

private:
    TLogLevel messageLevel;
};

// ===== log macros =====
#define LOG_DEBUG   Log().Get(DEBUG)
#define LOG_INFO    Log().Get(INFO)
#define LOG_ERROR   Log().Get(ERROR)
#define LOG_FATAL   Log().Get(FATAL)
#define LOG         Log().Get()

#endif //TUNGUSSKA_LOG_H
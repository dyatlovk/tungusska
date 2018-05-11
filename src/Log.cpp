#include "Log.h"

Log::Log() {};

Log::~Log()
{
    ss << std::endl;
    fprintf( stderr, "%s", ss.str().c_str() );
    fflush( stderr );
}

std::stringstream& Log::Get(TLogLevel level)
{
    tm localTime;
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t(t);
    localtime_r(&now, &localTime);
    const std::chrono::duration<double> tse = t.time_since_epoch();
    std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 100000;

    switch ( level )
    {
        case ERROR :
            ss << "\033[1;31m";
            ss 
                << (1900 + localTime.tm_year)
                << "-"
                << std::setfill('0') << std::setw(2) << (localTime.tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << localTime.tm_mday << " "
                << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
                << std::setfill('0') << std::setw(3) << milliseconds << " ";
            ss << "[ERR] ";
            break;
        case DEBUG:
            ss << "\033[1;33m";
            ss 
                << (1900 + localTime.tm_year)
                << "-"
                << std::setfill('0') << std::setw(2) << (localTime.tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << localTime.tm_mday << " "
                << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
                << std::setfill('0') << std::setw(3) << milliseconds << " ";
            ss << "[DBG] ";
            break;
        case INFO:
            ss << "\033[1;32m";
            ss 
                << (1900 + localTime.tm_year)
                << "-"
                << std::setfill('0') << std::setw(2) << (localTime.tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << localTime.tm_mday << " "
                << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
                << std::setfill('0') << std::setw(3) << milliseconds << " ";
            ss << "[INF] ";
            break;
        case FATAL:
            ss << "\033[1;31m";
            ss 
                << (1900 + localTime.tm_year)
                << "-"
                << std::setfill('0') << std::setw(2) << (localTime.tm_mon + 1) << "-"
                << std::setfill('0') << std::setw(2) << localTime.tm_mday << " "
                << std::setfill('0') << std::setw(2) << localTime.tm_hour << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_min << ':'
                << std::setfill('0') << std::setw(2) << localTime.tm_sec << '.'
                << std::setfill('0') << std::setw(3) << milliseconds << " ";
            ss << "[FTL] ";
            break;
        default: break;
    }
    messageLevel = level;
    return ss;
}
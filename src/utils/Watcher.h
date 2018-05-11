#ifndef TUNGUSSKA_WATCHER_H
#define TUNGUSSKA_WATCHER_H

#include <string>
#include <sys/inotify.h>

#include "../Log.h"

class Watcher 
{
    #define EVENT_SIZE  ( sizeof (struct inotify_event) )
    #define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

public:
    Watcher();
    ~Watcher();

    void watch( const char* file );

private:
    int fd;
    int length, i = 0, wd;
    char buffer[BUF_LEN];
};

#endif
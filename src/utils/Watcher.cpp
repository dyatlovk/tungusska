#include "Watcher.h"

Watcher::Watcher() = default;

Watcher::~Watcher()
{
    inotify_rm_watch( fd, wd );
};

void Watcher::watch( const char* file )
{
    fd = inotify_init();
    if ( fd < 0 )
        LOG_ERROR << "inotify_init";

    wd = inotify_add_watch( fd, file, IN_MODIFY | IN_CREATE | IN_DELETE );
    if (wd < 0) {
        LOG_ERROR << "Cannot add watch for" << file;
    } else {
        LOG_DEBUG << "start watching for " << file;
    }
}
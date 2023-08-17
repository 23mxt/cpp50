#include "Socket.h"
#include <Mycpphead.h>

Socket::Socket()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_fd == -1)
    {
        perror("socket");
    }
    
}

Socket::Socket(int fd)
:_fd(fd)
{}

Socket::~Socket()
{
    close(_fd);
}

int Socket::fd() const
{
    return _fd;
}

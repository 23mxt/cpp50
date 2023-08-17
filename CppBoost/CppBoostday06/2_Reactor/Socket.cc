#include "Socket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>


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
{

}
Socket::~Socket()
{
    close(_fd);
}

//返回文件描述符
int Socket::fd() const
{
    return _fd;
}

//shutdown的使用，用来关闭读端或写端
void Socket::shutdownWrite()
{
    int ret = shutdown(_fd,SHUT_WR);
    if(ret)
    {
        perror("shutdown");
        return;
    }
}

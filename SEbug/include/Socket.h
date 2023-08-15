#ifndef _SOCKET_H
#define _SOCKET_H
#include"NoCopyable.h"
class Socket:public NoCopyable
{
public:
    Socket();

    explicit Socket(int fd);

    ~Socket();

    int fd()const;
private:
    int _fd;
};

#endif //_SOCKET_H
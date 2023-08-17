#ifndef  _SOCKET_H_
#define _SOCKET_H_

#include "Nocopyable.h"

class Socket
{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();

    //返回文件描述符
    int fd() const;
    //shutdown的使用，用来关闭读端或写端
    void shutdownWrite();
private:
    int _fd;
};

#endif 

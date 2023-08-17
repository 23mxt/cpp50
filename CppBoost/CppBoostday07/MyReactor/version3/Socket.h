#ifndef _Socket_H_
#define _Socket_H_

#include "NonCopyable.h"

class Socket
:NonCopyable
{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();

    int fd() const;
private:
    int _fd;
};

#endif 


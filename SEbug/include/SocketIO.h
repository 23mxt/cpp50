#ifndef _SOCKETIO_H
#define _SOCKETIO_H
#include"NoCopyable.h"
#include <string>
using std::string;
struct Train{
    int length;
    int ID;
    char buff[4096];
};
class SocketIO
{
public:
    SocketIO(int fd);

    ~SocketIO();

    int readn(char *buf, int nbytes);

    int writen(const char *buf, int nbytes);

    int readLine(char *buf, int nbytes);

    int fd()const{
        return _fd;
    }
private:
    int _fd;
};

#endif //_SOCKETIO_H
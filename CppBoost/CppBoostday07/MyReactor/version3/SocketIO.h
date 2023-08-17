#ifndef _SocketIO_H_
#define _SocketIO_H_



class SocketIO
{
public:
    SocketIO(int fd);
    ~SocketIO() {}  //析构在socket Close
    
    int readn(char *buf, int len);
    int readline(char *buf, int len);
    int writen(const char *buf, int len);

private:
    int _fd;    
};

#endif 


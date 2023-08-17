#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

class SocketIO
{
public:
    explicit SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf, int len);
    int readLine(char *buf, int len);
    //表示写后的数据不能被修改
    int writen(const char *buf, int len);

private:
    int _fd;
};

#endif

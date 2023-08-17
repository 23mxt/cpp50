#ifndef  _SOCKETIO_H_
#define  _SOCKETIO_H_



class SocketIO
{
public:
    SocketIO(int fd);
    ~SocketIO();

    //读取一行
    int readline(char *buf, int len);
    //读取n个字节，读不到不退出循环
    int readn(char *buf, int len);
    //写最多n个字节
    //加了const可以写入，不允许别人修改
    int write(const char *buf, int len);
private:
    int _fd;
};

#endif 

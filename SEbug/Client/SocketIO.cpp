/**
 * Project CPP49
 */

#include <unistd.h>
#include "SocketIO.h"
#include <sys/types.h>
#include <sys/socket.h>
#include<cstring>
#include<iostream>
using std::cout;
using std::endl;
using std::cerr;
/**
 * SocketIO implementation
 */

/**
 * @param fd
 */
SocketIO::SocketIO(int fd) : _fd(fd)
{
}

SocketIO::~SocketIO()
{
    close(_fd);
}
/**
 * @param buf
 * @param len
 * @return string
 */
int SocketIO::recvn(char *buf, size_t len)
{
    int left = len;
    char *pstr = buf;
    while (left > 0)
    {
        int sret = read(_fd, pstr, len);
        if (sret == -1)
        {
            ::perror("read");
            return -1;
        }
        else if (sret == 0)
        {
            break;
        }
        else
        {
            left -= sret;
            pstr += sret;
        }
    }
    return len - left;
}

/**
 * @param buf
 * @param len
 * @return void
 */
int SocketIO::writen(const Train &train)
{
    int left = sizeof(train._length) + sizeof(train._id) + train._length;
    const Train *pstr = &train;
    while (left > 0)
    {
        int sret = send(_fd, pstr, left, MSG_NOSIGNAL);
        if (sret == -1 && errno == EINTR)
        {
            continue;
        }
        else if (sret == -1)
        {
            ::perror("send");
            return -1;
        }
        else if (sret == 0)
        {
            break;
        }
        else
        {
            pstr += sret;
            left -= sret;
        }
    }
    return sizeof(train._length) + sizeof(train._id) + train._length - left;
}

/**
 * @param buf
 * @param len
 * @return string
 */
int SocketIO::readLine(char *buf, size_t len)
{
    //接收length 根据小火车协议
    int length=0;
    int ret =recvn(buf,sizeof(length));
    if(ret !=4){
        // ::perror("readLine recv length");
        cerr<<"readLine recv length = "<<ret<<endl;
        return -1;
    }
    memcpy(&length,buf,sizeof(length));
    //接收ID
    memset(buf,0,len);
    int ID=0;
    ret = recvn(buf,sizeof(ID));
    if(ret!=4){
        ::perror("readLine recvn ID");
        return -1;
    }
    memcpy(&ID,buf,sizeof(ID));
    memset(buf,0,len);
    ret = recvn(buf,length);
    if(ret==-1)
        ::perror("readLine recvn message");
    return ID;
}

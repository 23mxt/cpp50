#include "SocketIO.h"
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


SocketIO::SocketIO(int fd)
    :_fd(fd)
{

}

SocketIO::~SocketIO()
{
    close(_fd); //Socket析构也会close，注意会不会close两次，如果会
                //将导致未定义的行为
}

int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char* pstr = buf;
    int ret = 0;    //read的返回值
    
    while(1)
    {
        ret = read(_fd, pstr, left);
        if((ret == -1) && (errno = EINTR))
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("read error -1");
            return left - ret;
        }
        else if(ret == 0)
        {
            //读满，退出
            break;
        }
        else
        {
            left -= ret;
            pstr += ret;
        }
    }

    return left - ret;
}
int SocketIO::readline(char *buf, int len)
{
    //最后一位给换行符
    int left = len - 1;
    char* pstr = buf;
    int ret = 0, total = 0;    
    
    while(1)
    {
        ret = read(_fd, pstr, left);
        if((ret == -1) && (errno = EINTR))
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("read error -1");
            return left - ret;
        }
        else if(ret == 0)
        {
            break;
        }
        else
        {
            //检查是否读到了换行符
            for(int idx = 0; idx <= ret; idx++)
            {
                if(pstr[idx] == '\n')
                {
                    pstr[idx] = '\0';   
                    total += ret;
                    return total;
                }
            }
            
            left -= ret;
            pstr += ret;
            total += ret;
        }
    }

    //没检查到换行符，直接手动添加
    *pstr = '\0';

    return left - ret;
}
//写最多n个字节
int SocketIO::write(const char *buf, int len)
{
    int left = len;
    const char* pstr = buf;
    int ret = 0;    
    
    while(1)
    {
        ret = ::write(_fd, pstr, left);
        if((ret == -1) && (errno = EINTR))
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("write error -1");
            return left - ret;
        }
        else if(ret == 0)
        {
            //读满，退出
            break;
        }
        else
        {
            left -= ret;
            pstr += ret;
        }
    }

    //写入成功，返回0
    return left - ret;
}



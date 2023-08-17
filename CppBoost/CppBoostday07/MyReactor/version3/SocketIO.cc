#include "SocketIO.h"
#include <Mycpphead.h>

SocketIO::SocketIO(int fd)
:_fd(fd)
{}

int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char* pstr = buf;
    int ret = 0;
    
    while(left > 0)
    {
        ret = read(_fd, pstr, left);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        } else if(ret == -1) {
            perror("readn error");
            return -1;
        } else if(ret == 0) {
            break;
        } else {
            left -= ret;
            pstr += ret;
        }
    }

    return len - left;
}

int SocketIO::readline(char *buf, int len)
{
    int left = len - 1;
    char* pstr = buf;
    int ret = 0, total = 0;
    
    while(left > 0)
    {
        //只拷贝不清空，预读
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        } else if(ret == -1) {
            perror("readline error");
            return -1;
        } else if(ret == 0) {
            break;
        } else {
            //判断有无换行符
            for(int idx = 0; idx < ret; ++idx)
            {
               if( pstr[idx] == '\n')
               {
                   pstr[idx] = '\0';
                   int sz = idx + 1;
                   read(_fd, pstr, sz);
                    return total + sz;
               }
            }

            read(_fd, pstr, ret);
            total += ret;
            left -= ret;
            pstr += ret;
        }
    }

    //未找到换行符
    *pstr = '\0';
    return total;
}
int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char* pstr = buf;
    int ret = 0;
    
    while(left > 0)
    {
        ret = write(_fd, pstr, left);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        } else if(ret == -1) {
            perror("write error");
            return -1;
        } else if(ret == 0) {
            break;
        } else {
            left -= ret;
            pstr += ret;
        }
    }

    return len - left;

}

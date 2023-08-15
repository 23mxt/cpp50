#include "../include/SocketIO.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<cstring>
#include<iostream>
using std::cout;
using std::endl;
SocketIO::SocketIO(int fd):_fd(fd){
}

SocketIO::~SocketIO() {
    close(_fd);
}

int SocketIO::readn(char* buf, int nbytes) {
    int left = nbytes;
    char* pstr = buf;
    int ret = 0;
    while(left>0){
        ret = recv(_fd,pstr,left,0);
        if(ret ==-1){
            perror("recv");
            return -1;
        }else if (ret ==0){
            break;
        }else{
            pstr+=ret;
            left-=ret;
        }
    }
    return nbytes-left;
}

int SocketIO::writen(const char* buf, int nbytes) {
    int left = nbytes;
    const char* pstr = buf;
    int ret = 0;
    while(left>0){
        ret = send(_fd,pstr,left,0);
        if(ret ==-1&&errno==EINTR){
            continue;
        }else if(ret ==-1){
            return -1;
        }else if(ret ==0){
            break;
        }else{
            pstr+=ret;
            left-=ret;
        }
    }
    return nbytes-left;
}

int SocketIO::readLine(char* buf, int nbytes) {
    Train train;
    //采用百度网盘的小火车协议
    //消息定义格式： 消息内容长度 消息ID（1 关键字推荐 2 网页查询）消息内容 
    //接收火车协议中的buff长度 并初始化train.length
    memset(buf,0,nbytes);
    readn(buf,sizeof(train.length));
    memcpy(&train.length,buf,sizeof(train.length));
    //初始化火车协议中的ID
    memset(buf,0,nbytes);
    readn(buf,sizeof(train.ID));
    memcpy(&train.ID,buf,sizeof(train.ID));
    //初始化train.buff
    memset(buf,0,nbytes);
    readn(buf,train.length);
    memcpy(train.buff,buf,train.length);
    memset(buf,0,nbytes);
    memcpy(buf,&train,sizeof(train.length)+sizeof(train.ID)+train.length);

    return sizeof(train.length)+sizeof(train.ID)+train.length;
}

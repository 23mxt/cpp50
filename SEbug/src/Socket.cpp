#include "../include/Socket.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<iostream>
#include<unistd.h>
Socket::Socket()
{
    _fd = socket(AF_INET,SOCK_STREAM,0);
    if(_fd<0){
        perror("socket");
        exit(-1);
    }
}

Socket::Socket(int fd)
:_fd(fd)
{
}

Socket::~Socket()
{
    if(_fd>=0)
        close(_fd);
}

int Socket::fd()const
{
    return _fd;
}
/**
 * Project CPP49
 */


#include "Socket.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
/**
 * Socket implementation
 */


Socket::Socket():
_sockfd(socket(AF_INET,SOCK_STREAM,0)){
    
}

/**
 * @param fd
 */
Socket::Socket(int fd):_sockfd(fd){

}

Socket::~Socket() {
    if(_sockfd>=0)
        close(_sockfd);
}

/**
 * @return int
 */
int Socket::fd() {
    return _sockfd;
}
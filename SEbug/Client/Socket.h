/**
 * Project CPP49
 */


#ifndef _SOCKET_H
#define _SOCKET_H

class Socket {
public: 
    
Socket();
    
/**
 * @param fd
 */
explicit Socket(int fd);
    
~Socket();
    
int fd();
private: 
    int _sockfd;
};

#endif //_SOCKET_H
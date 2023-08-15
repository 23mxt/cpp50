/**
 * Project CPP49
 */


#ifndef _SOCKETIO_H
#define _SOCKETIO_H
#include<string>
#include "train.h"
using std::string;
class SocketIO {
public: 
    
/**
 * @param fd
 */
explicit SocketIO(int fd);
~SocketIO();
    
/**
 * @param buf
 * @param len
 */
int recvn(char * buf, size_t len);
    
/**
 * @param buf
 * @param len
 */
int writen(const Train& train);
    
/**
 * @param buf
 * @param len
 */
int fd(){
    return _fd;
}
int readLine(char* buf, size_t len);
private: 
    int _fd;
};
#endif //_SOCKETIO_H
#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include"SocketIO.h"
#include<string>
#include<functional>
#include<memory>
#include "train.h"
#include<nlohmann/json.hpp>
#include<iostream>
#include<unistd.h>
using std::cout;
using std::endl;
using json = nlohmann::json;
using std::string;
class TcpConnection
{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    int send(const Train &train);
    string receive();
    int fd();
private:
    SocketIO _sockio;

};

#endif //_TCPCONNECTION_H
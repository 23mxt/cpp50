#include "TcpServer.h"
#include <iostream>
using std::cout;
using std::endl;


TcpServer::TcpServer(const string & ip, unsigned short port)
: _acceptor(ip, port)
, _loop(_acceptor)
{}

void TcpServer::start()
{
    _acceptor.ready();
    _loop.loop();
}

void TcpServer::stop()
{
    _loop.unloop();
}

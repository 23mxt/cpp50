#include "TcpServer.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;


void onConnection(const TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
}

void onMessage(const TcpConnectionPtr & conn)
{
    //获取数据
    string msg = conn->receive();
    cout << "receive from client:" << msg << endl;
    //对数据进行处理

    //回显操作
    conn->send(msg);
}

void onClose(const TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has closed!" << endl;
}

void test()
{
    TcpServer server("127.0.0.1", 8888);
    server.setAllCallbacks(onConnection, onMessage, onClose);
    server.start();
}

int main()
{
    test();
    return 0;
}


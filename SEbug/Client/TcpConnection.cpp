#include "TcpConnection.h"
#include<sys/types.h>
#include<sys/socket.h>
int TcpConnection::fd(){
    return _sockio.fd();
}
TcpConnection::TcpConnection(int fd):_sockio(fd){
}
TcpConnection::~TcpConnection() {

}

int TcpConnection::send(const Train& train) {
    return _sockio.writen(train);
}

string TcpConnection::receive() {
    char msg[10240]= {0};
    int ID=_sockio.readLine(msg,sizeof(msg));
    if(ID==-1){
        close(fd());
        std::cerr<<"server is closed"<<endl;
        exit(-1);
    }
    if(ID ==100){
        string tmp(msg);
        json j = json::parse(tmp);
        cout<<endl;
        for(auto&elem:j){
            cout<<string(elem[0])<<endl;
        }
        cout<<endl;
    }else if(ID==200){
        string tmp(msg);
        json j = json::parse(tmp);
        for(auto&elem:j){
            std::cout<<"标题:"<<endl;
            cout<<string(elem[0][0])<<endl;
            cout<<"链接:"<<endl;
            cout<<string(elem[0][1])<<endl;
            cout<<"摘要:"<<endl;
            cout<<string(elem[0][2])<<endl<<endl;
        }
    }
    return msg;
}

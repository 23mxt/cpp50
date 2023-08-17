#include "Acceptor.h"
#include "TcpConnection.h"
#include <iostream>

using std::cout;
using std::endl;

void test()
{
    Acceptor acceptor("127.0.0.1", 8888);
    acceptor.ready();

    //建立连接
    TcpConnection Con(acceptor.accept());

    //调试
    cout << "the connect has established " << Con.toString() << endl;

    int cnt = 1;
    while(1)
    {
        cout << ">> recv msg from client: " << Con.receive() << endl;
        Con.send("hello, tml");
        cout << "this is " << cnt << "recv" << endl;
    }


}

int main()
{
    test();
    return 0;
}

#include"../include/SearchEngineServer.h"

void test(){
    SearchEngineServer server("127.0.0.1",8888);
    server.start();
}
int main(){
    test();
    return 0;
}

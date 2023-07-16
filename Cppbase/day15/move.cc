#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::move;
using std::string;

int main() {
    int a = 10;
    int &&ref = move(move(a));
    cout << ref << endl;
    return 0;
}


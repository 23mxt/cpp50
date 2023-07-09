#include <string.h>
#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;
using std::string;

bool readNum(float & num) {
    if(cin.bad()) {
        cout << "cin is broken!" << endl;
        cout << "tmp not use it" << endl;
        return false;
    }else if(cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        //cout << "请输入一个数字：" << endl;
        return false;
    }else {
        //输入合法
        cout << "num" << num << endl;
        if(cin.peek() == '\n') {
            return true;
        }
        return false;
    }
}

int main() {
    float num;
    cin >> num;
    bool ret;
    ret = readNum(num);
    if(ret) {
        cout << "this is a num!" << endl;
    }else {
        cout << "this is not a num!" << endl;
    }
    return 0;
}


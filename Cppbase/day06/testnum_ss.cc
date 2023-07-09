#include <string.h>
#include <iostream>
#include <sstream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::istringstream;

bool readNum(string & isnum) {
    float num;
    istringstream iss(isnum);
    
    iss >> num;
    cout << "before num " << num << endl;

    string remainstr;
    getline(iss, remainstr);
    cout << remainstr << endl;

    if(iss.bad()) {
        cout << "iss is broken!" << endl;
        cout << "tmp not use it" << endl;
        return false;
    }else if(iss.fail()) {
        iss.clear();
        iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "请输入一个数字：" << endl;
        return false;
    }else if(iss.good()){
        //输入合法
        cout << "num" << num << endl;
    }else {
        cout << "goin?" << endl;
    }

    cout << remainstr << endl;
    /* if(remainstr.compare("\n")) { */
    /*     return true; */
    /* } */

    if(!remainstr.empty()) {
        cout << "goin?" << endl;
        return false;
    }
    return true;
}

int main() {
    string isnum;
    cin >> isnum;

    bool ret;
    ret = readNum(isnum);
    if(ret) {
        cout << "this is a num!" << endl;
    }else {
        cout << "this is not a num!" << endl;
    }
    return 0;
}


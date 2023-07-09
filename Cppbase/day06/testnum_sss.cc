#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

bool isNum(string & num) {
    size_t i = 0;
    while(num[i] == ' ') {
        ++i;
    }

    bool isnum = flase;
    if(num[i] == '.'){
        ++i;
        isnum = true;
    }

    while(isdigit(num[i])) {
        ++i;
        isnum = true;
    }


}

int main() {
    string num;
    cin >> num;

    bool res;
    res = isNum(num);
    if(res) {
        cout << "this is a num" << endl;
    }
    else {
        cout << "this is a num" << endl;
    }
    return 0;
}


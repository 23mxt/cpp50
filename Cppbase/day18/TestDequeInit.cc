#include <string.h>
#include <iostream>
#include <deque>
using std::cout;
using std::endl;
using std::string;
using std::deque;

int main() {
    deque<int> numbers;
    cout << "sizeof(deque)" << sizeof(numbers) << endl;
    deque<int> numbers2{1, 2, 4};
    cout << "sizeof(deque2)" << sizeof(numbers2) << endl;
    return 0;
}


#include <iostream>
#include <utility>
#include <string>

using std::cout;
using std::endl;
using std::pair;
using std::string;

void test()
{
    pair<int, double> number = {1, 33.33};
    cout << number.first << "    " << number.second << endl;

    pair<string, int> number2 = {"hello", 10};
    cout << number2.first << "    " << number2.second << endl;
}

int main(int argc, char **argv)
{
    test();
    return 0;
}



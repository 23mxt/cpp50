#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

template <typename T>
class Outside
{
public:
template <typename R>
    class Inside
    {
    public:
        Inside(R x)
        :_r(x)
        {}

        void disp()
        {
            cout << "Inside _r = " << _r << endl;
        }
    private:
        R _r;
    };
    
    Outside(T x)
    :_t(x)
    {}

    void disp()
    {
        cout << "Outside";
        _t.disp();
    }
private:
    Inside<T> _t;
};
int main() {
    Outside<int>::Inside<double> obin(3.5);
    obin.disp();

    Outside<int> obout(2);
    obout.disp();
    return 0;
}


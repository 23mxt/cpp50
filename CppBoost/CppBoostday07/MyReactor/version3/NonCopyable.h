#ifndef _NonCopyable_H_
#define _NonCopyable_H_

class NonCopyable
{
public:
    NonCopyable() {}
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};

#endif 


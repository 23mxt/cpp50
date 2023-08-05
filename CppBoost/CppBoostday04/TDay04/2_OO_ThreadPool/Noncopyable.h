#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

class Noncopyable
{
/* public: */
protected:
    Noncopyable(){}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable &rhs) = delete;
    Noncopyable &operator=(const Noncopyable &rhs) = delete;
};

#endif

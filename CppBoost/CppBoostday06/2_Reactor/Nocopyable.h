#ifndef _NOCOPY_H_
#define _NOCOPY_H_

class Nocopyable
{
public:
    Nocopyable() {}
    ~Nocopyable() {}

private:
    Nocopyable(const Nocopyable &) = delete; 
    Nocopyable &operator=(const Nocopyable &) = delete;
};

#endif

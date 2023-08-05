#ifndef  _NOCOPYABLE_H_
#define _NOCOPYABLE_H_ 

class Nocopyable
{
public:
    Nocopyable() {}
    ~Nocopyable() {}

    Nocopyable(const Nocopyable &) = delete;
    Nocopyable &operator=(const Nocopyable &) = delete;

};

#endif 

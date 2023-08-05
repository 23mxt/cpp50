#pragma once

class Nocopyable
{
public:
    Nocopyable() {}
    ~Nocopyable() {}

private:
    Nocopyable(const Nocopyable &nocopyable);
    Nocopyable operator=(const Nocopyable &);
};


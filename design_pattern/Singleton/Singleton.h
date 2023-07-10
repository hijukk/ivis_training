#include <iostream>

class Singleton
{
public:
    static Singleton& getInstance();

private:
    Singleton();
    ~Singleton();
    Singleton& operator=(const Singleton& src) = delete;
    Singleton& operator=(const Singleton&& src) = delete;
    Singleton(const Singleton& src) = delete;
    Singleton(const Singleton&& src) = delete;
};



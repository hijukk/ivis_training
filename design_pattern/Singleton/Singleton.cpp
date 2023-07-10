#include <iostream>
#include <functional>
#include "Singleton.h"

Singleton& Singleton::getInstance()
{
    static Singleton instance;

    return std::ref(instance);
}

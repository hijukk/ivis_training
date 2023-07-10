#include <iostream>
#include <thread>
#include "Observer.hpp"

int main()
{
    Subject subject;
    std::shared_ptr<Observer1> ob1 = std::make_shared<Observer1>();
    std::shared_ptr<Observer2> ob2 = std::make_shared<Observer2>();

    // std::thread thread1([&](){ subject.attach(ob1); });
    // std::thread thread2([&](){ subject.attach(ob2); });
    // std::thread thread3([&](){ subject.setNum(111,222); });

    // thread1.join();
    // thread2.join();
    // thread3.join();
    
    subject.attach(ob1);
    subject.attach(ob2);
    subject.setNum(11, 22);
    
    std::cout << "Observer detached..." << std::endl;

    subject.detach(ob2);
    subject.setNum(99, 88);


    return 0;
}

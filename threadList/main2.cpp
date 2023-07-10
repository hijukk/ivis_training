#include <iostream>
#include <memory>
#include "my_list.h"
#include <vector>
#include <thread>
#include <random>
#include <chrono>

void push_back_front(MyList<int>& ml)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 10);
    std::uniform_int_distribution<int> dis2(0, 1);

    for(int i = 0; i < 30; ++i)
    {
        int rand = dis(gen);
        if(dis2(gen) == 0)
        {
            std::string log = "push_back.. " + std::to_string(rand);
            std::cout << log << std::endl;
            ml.push_back(rand);
        }
        else
        {
            std::string log = "push_front.. " + std::to_string(rand);
            std::cout << log << std::endl;
            ml.push_front(rand);
        }
    }
}

void pop_back_front(MyList<int>& ml)
{
    for(int i = 0; i < 30; ++i)
    {
        if(1 == (i % 2))
        {
            std::cout << "pop_back.." << std::endl;
            ml.pop_back();
        }
        else
        {
            std::cout << "pop_front.." << std::endl;
            ml.pop_front();
        }
    }
}

void find_erase(MyList<int>& ml)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    MyList<int>::MyIterator it;

    while(ml.end() != it)
    {
        it = ml.find(7);
        ml.erase(it);
    }
}

void print_list(MyList<int>& ml)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    MyList<int>::MyIterator it = ml.begin();

    while(ml.end() != it)
    {
        std::string log = "log.." + std::to_string(*it);
        std::cout << log << std::endl;
        ++it;
    }

    do
    {
        --it;
        std::string log = "log.." + std::to_string(*it);
        std::cout << log << std::endl;
    } while (it != ml.begin());
}


int main()
{

    MyList<int> ml01;
    for(int i = 21; i < 61; ++i)
    {
        ml01.push_back(i);
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << std::endl;

    std::thread insert_t(push_back_front, std::ref(ml01));
    std::thread erase_t(pop_back_front, std::ref(ml01));
    // std::thread find_t(find_erase, std::ref(ml01));
    // std::thread print_t(print_list, std::ref(ml01));
    // std::thread clear_t(&MyList<int>::clear, &ml01);

    insert_t.join();
    erase_t.join();
    // find_t.join();
    // print_t.join();
    // clear_t.join();


    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << std::endl;

    return 0;
}

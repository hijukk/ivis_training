#include <iostream>
#include <memory>
#include "my_list.h"
#include <vector>
#include <thread>

void b_erase(MyList<int>& ml)
{
    MyList<int>::MyIterator it = ml.begin();
    ml.erase(it);
}

void e_erase(MyList<int>& ml, MyList<int>::MyIterator& it)
{
    ml.erase(it);
}




int main()
{
    std::cout << "======= insert begin() =======" << std::endl;

    MyList<int> ml01;
    MyList<int>::MyIterator it = ml01.begin();
    std::vector<std::thread> insert_thread;

    for(int i = 0; i < 2; ++i)
    {
        insert_thread.emplace_back(std::thread(&MyList<int>::insert, &ml01, it, i));
    }

    for(std::thread& i : insert_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    insert_thread.clear();

    std::cout << "======= insert else =======" << std::endl;

    it = ml01.begin();
    ++it;

    for(int i = 11; i < 13; ++i)
    {
        insert_thread.emplace_back(std::thread(&MyList<int>::insert, &ml01, it, i));
    }

    for(std::thread& i : insert_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    insert_thread.clear();

    std::cout << "======= insert end() =======" << std::endl;

    it = ml01.end();

    for(int i = 3; i < 7; ++i)
    {
        insert_thread.emplace_back(std::thread(&MyList<int>::insert, &ml01, it, 7));
    }

    for(std::thread& i : insert_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    insert_thread.clear();
    
    
    std::cout << "======= erase find =======" << std::endl;
    
    std::vector<std::thread> erase_thread;

    for(int i = 0; i < 3; ++i)
    {
        erase_thread.emplace_back(std::thread(static_cast<void(MyList<int>::*)(const int&)>(&MyList<int>::erase), &ml01, 7));
    }

    for(std::thread& i : erase_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    erase_thread.clear();

    std::cout << "======= erase begin() =======" << std::endl;
    
    it = ml01.begin();

    for(int i = 0; i < 3; ++i)
    {
        erase_thread.emplace_back(std::thread(b_erase, std::ref(ml01)));
    }

    for(std::thread& i : erase_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    erase_thread.clear();

    std::cout << "======= erase else =======" << std::endl;

    it = ml01.begin();
    --it;
    for(int i = 0; i < 2; ++i)
    {
        erase_thread.emplace_back(std::thread(e_erase, std::ref(ml01), std::ref(it)));
    }

    for(std::thread& i : erase_thread)
    {
        i.join();
    }

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    erase_thread.clear();

    std::cout << "======= assign =======" << std::endl;

    MyList<int> ml02;
    std::vector<std::thread> assign_thread;

    for(int i = 0; i < 100; ++i)
    {
        assign_thread.emplace_back(std::thread(&MyList<int>::assign, &ml02, ml01));
    }

    for(std::thread& e : assign_thread)
    {
        e.join();
    }

    for(MyList<int>::MyIterator it = ml02.begin(); it != ml02.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    assign_thread.clear();

    std::cout << "======= find =======" << std::endl;

    std::vector<std::thread> find_thread;

    for(int i = 0; i < 2; ++i)
    {
        find_thread.emplace_back(std::thread(&MyList<int>::find, &ml02, 1));
    }

    for(std::thread& f : find_thread)
    {
        f.join();
    }

    find_thread.clear();

    return 0;
}

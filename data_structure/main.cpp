#include <iostream>
#include <memory>
#include "my_list.h"
#include <list>

int main()
{
    // MyList<int> mlll01;
    // mlll01.push_back(1);
    // mlll01.push_back(2);
    // mlll01.push_front(3);
    // mlll01.push_front(4);
    

    // mlll01.insert(mlll01.find(3), 7);

    // // MyList<int> mlll02(mlll01);

    // for(MyList<int>::MyIterator it = mlll01.begin(); it != mlll01.end(); ++it)
    // {
    //     std::cout << *it;
    // }
    // std::cout  << std::endl;
    
    // return 0;

    MyList<int> ml01;

    std::cout << "empty(): " << ml01.empty() << std::endl;

    ml01.push_back(1);
    ml01.push_back(2);
    ml01.push_back(3);
    ml01.push_back(4);

    int i;
    ml01.push_back(i);

    ml01.push_front(7);
    ml01.push_front(6);
    ml01.push_front(5);
    
    std::cout << "front element: " << ml01.front() << std::endl;
    std::cout << "back element: " << ml01.back() << std::endl;

    std::cout << "empty(): " << ml01.empty() << std::endl;

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========erase end(), nullptr ========" << std::endl;

    ml01.erase(ml01.end());
    // ml01.erase(nullptr);

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========opeartor = ========" << std::endl;
    
    MyList<int> mll02;
    // mll02.push_back(11);
    // mll02.assign(ml01);
    mll02 = ml01;
    ml01.pop_back();

    std::cout << "ml01: ";

    for(auto i : ml01)
    {
        std::cout << i ;
    }

    std::cout << std::endl;

    std::cout << "mll02: ";

    for(auto i : mll02)
    {
        std::cout << i ;
    }

    std::cout << std::endl;

    // return 0;

    std::cout << "========pop_front========" << std::endl;
    ml01.pop_front();
    ml01.pop_front();
    ml01.pop_front();
    // ml01.pop_front();
    // ml01.pop_front();
    // ml01.pop_front();
    // ml01.pop_front();

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "========reverse========" << std::endl;
    
    if (ml01.getSize() > 0)
    {
        MyList<int>::MyIterator it = ml01.end();
        do
        {
            --it;
            std::cout << *it << std::endl;
        } while (it != ml01.begin());
    }

    std::cout << "size : " << ml01.getSize() << std::endl;
    
    std::cout << "========pop_back========" << std::endl;
    ml01.pop_back();
    ml01.pop_back();
    ml01.pop_back();
    ml01.pop_back();

    // std::cout << ml01.getSize() << std::endl;
    // std::cout << ml01.head << std::endl;

    // if (ml01.begin() != ml01.end())
    //     MyList<int>::MyIterator itt = ml01.begin();
    //     std::cout << "ml01.begin(): " << *itt << std::endl;

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========insert========" << std::endl;
    MyList<int>::MyIterator b_it = ml01.begin();
    ml01.insert(b_it, 8);

    MyList<int>::MyIterator e_it = ml01.end();
    b_it = ml01.begin();
    ml01.insert(++b_it, 9);
    ml01.insert(e_it, 10);

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }    

    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========erase========" << std::endl;
    ml01.erase(10);

    // e_it = --(ml01.end());
    // ml01.erase(e_it);

    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========find========" << std::endl;

    MyList<int>::MyIterator find_it = ml01.find(2);
    std::cout << "find_it: " << *find_it << std::endl;
    find_it = ml01.find(8);
    std::cout << "find_it: " << *find_it << std::endl;

    // MyList<int>::MyIterator iit = ml01.begin();
    // std::cout << "--(--iit): " << *--(--iit) << std::endl;
    // iit = ml01.end();
    // std::cout << "++iit: " << *++iit << std::endl;

    std::cout << "========copy constructor========" << std::endl;
    
    MyList ml02(ml01);
    std::cout << "<ml02>" << std::endl;

    for(MyList<int>::MyIterator it = ml02.begin(); it != ml02.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml02.getSize() << std::endl;


    std::cout << "========move constructor========" << std::endl;

    MyList ml03(static_cast<MyList<int>&&>(ml01));

    std::cout << "<ml03>" << std::endl;
    for(MyList<int>::MyIterator it = ml03.begin(); it != ml03.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml03.getSize() << std::endl;

    std::cout << "<ml01>" << std::endl;
    for(MyList<int>::MyIterator it = ml01.begin(); it != ml01.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml01.getSize() << std::endl;

    std::cout << "========assign========" << std::endl;

    MyList<int> ml04;
    ml04.assign(ml03);

    std::cout << "<ml03>" << std::endl;
    for(MyList<int>::MyIterator it = ml03.begin(); it != ml03.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml03.getSize() << std::endl;

    std::cout << "<ml04>" << std::endl;
    for(MyList<int>::MyIterator it = ml04.begin(); it != ml04.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml04.getSize() << std::endl;

    std::cout << "========opearator= ========" << std::endl;

    MyList<int> ml05;
    ml05 = ml03;

    std::cout << "<ml03>" << std::endl;
    for(MyList<int>::MyIterator it = ml03.begin(); it != ml03.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml03.getSize() << std::endl;

    std::cout << "<ml05>" << std::endl;
    for(MyList<int>::MyIterator it = ml05.begin(); it != ml05.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << "size : " << ml05.getSize() << std::endl;

    std::cout << "========clear========" << std::endl;
    ml05.clear();

    for(MyList<int>::MyIterator it = ml05.begin(); it != ml05.end(); ++it)
    {
        std::cout << *it << std::endl;
    }    

    std::cout << "size : " << ml05.getSize() << std::endl;
}
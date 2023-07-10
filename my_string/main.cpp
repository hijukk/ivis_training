#include <iostream>
#include "my_string.h"
#include <string>

int main(){

    std::string str = "aaa";
    str.at(0);

    char str01[6] = "hello";
    char str02[4] = "bye";
    MyString ms01;

    // setValue()
    ms01.setValue(str01);
    // getValue()
    std::cout << "ms01: "<< ms01.getValue() << std::endl;

    //at()
    std::cout << "ms01.at(-1): " << ms01.at(-1) << std::endl;
    std::cout << "ms01.at(10): " << ms01.at(10) << std::endl;
    std::cout << "ms01.at(3): " << ms01.at(3) << std::endl;
    //operator[]
    std::cout << "ms01[-2]: " << ms01[-2] << std::endl;
    std::cout << "ms01[6]: " << ms01[6] << std::endl;
    std::cout << "ms01[4]: " << ms01[4] << std::endl;

    std::cout << std::endl;

    // operator==
    std::cout << "str01 == ms01: " << (str01 == ms01) << std::endl;
    std::cout << "str02 == ms01: " << (str02 == ms01) << std::endl;
    // operator!=
    std::cout << "str01 != ms01: " << (str01 != ms01) << std::endl;
    std::cout << "str02 != ms01: " << (str02 != ms01) << std::endl;

    // operator+
    ms01 = str02 + ms01;
    std::cout << "str02 + ms01: " << ms01.getValue() << std::endl;

    // operator<<
    std::cout << "ms01: " << ms01 << std::endl;

    // getLength()
    std::cout << "ms01.getLength(): " << ms01.getLength() << std::endl;

    std::cout << std::endl;

    MyString ms02 = MyString("abcdefg");
    std::cout << "ms02: " << ms02 << std::endl;

    // reverse()
    ms02.reverse();
    std::cout << "ms02.reverse(): " << ms02 << std::endl;
    // clear()
    ms02.clear();
    // std::cout << "ms02.clear(): " << ms02 << std::endl; //null

    std::cout << std::endl;

    MyString ms03("This : ");
    // insert()
    ms03.insert(5, "is");
    std::cout << "ms03.insert(): " << ms03 << std::endl;
    // append()
    ms03.append("Test Test");
    std::cout << "ms03.append(): " << ms03 << std::endl;

    // find()
    MyString ms04("Te");
    MyString ms05("This is: Test Test ab");

    MyString mss01("abcd");
    MyString mss02("");
    MyString mss03;
    MyString mss04("ab");
    MyString mss05("a");

    std::cout << "ms03.find(): " << ms03.find(ms04) << std::endl;
    // replace()
    // ms03.replace(ms04, mss01);
    // ms03.replace(ms04, mss02);
    // ms03.replace(ms04, mss03);
    ms03.replace(ms04, mss04);
    // ms03.replace(ms04, mss05);
    // ms03.replace(ms05, mss05);
    std::cout << "ms03.replace(): " << ms03 << std::endl;

    std::cout << std::endl;

    // move()
    std::cout << "before ms04: " << ms04 << std::endl;
    std::cout << "before mss01: " << mss01 << std::endl;
    ms04.move(static_cast<MyString&&>(mss01));
    std::cout << "after ms04: " << ms04 << std::endl;
    // std::cout << "after mss01: " << mss01 << std::endl; //nullptr
    // if(mss01.getValue() == nullptr)
    // {
    //     std::cout << "nullptr" << std::endl;
    // }

    std::cout << std::endl;

    // substr()
    std::cout << "ms03: " << ms03 << std::endl;
    std::cout << "ms03.substr(): " << ms03.substr(5,7) << std::endl;

    std::cout << std::endl;

    // compare()
    MyString ms06("apple");
    std::cout << "ms06: " << ms06 << std::endl;
    std::cout << "ms06.compare(apple): " << ms06.compare("apple") << std::endl;
    std::cout << "ms06.compare(app): " << ms06.compare("app") << std::endl;
    std::cout << "ms06.compare(banana): " << ms06.compare("banana") << std::endl;

    std::cout << std::endl;

    // operator+
    std::cout << "ms01: " << ms01 << std::endl;
    std::cout << "ms06 + ms01: " << ms06 + ms01 << std::endl;
    // operator+=
    ms01 += ms06;
    std::cout << "ms01 += ms06: " << ms01 << std::endl;

    std::cout << std::endl;

    // operator=
    std::cout << "before ms01: " << ms01 << std::endl;
    std::cout << "before ms06: " << ms06 << std::endl;
    ms01 = ms06;
    std::cout << "after ms01: " << ms01 << std::endl;
    std::cout << "after ms06: " << ms06 << std::endl;

    std::cout << std::endl;

    // operator==
    std::cout << "ms06 == apple: " << (ms06 == "apple") << std::endl;
    std::cout << "ms06 == app: " << (ms06 == "app") << std::endl;
    std::cout << "ms06 == banana: " << (ms06 == "banana") << std::endl;

    // operator!=
    std::cout << "ms06 != apple: " << (ms06 != "apple") << std::endl;
    std::cout << "ms06 != app: " << (ms06 != "app") << std::endl;
    std::cout << "ms06 != banana: " << (ms06 != "banana") << std::endl;


}
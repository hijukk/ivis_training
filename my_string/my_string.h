#include <iostream>

class MyString;

MyString operator+(const char* str, const MyString& ms);

std::ostream& operator<<(std::ostream& out, const MyString& ms);

bool operator==(const char* str, const MyString& ms);
bool operator!=(const char* str, const MyString& ms);

class MyString {

public:
    MyString();
    explicit MyString(const char* str);
    MyString(const MyString& ms);
    MyString(MyString&& ms);
    ~MyString();

public:

    inline int getLength() const
    {
        return mystrLength;
    }
    void reverse();
    void clear();

    void setValue(char* str);
    char* getValue() const;
    char at(const int pos) const;
    char operator[](const int pos) const;

    void insert(const int pos, const char* str);
    void append(const char* str);
    int find(const MyString& find_ms, const int start=0) const;
    void replace(const MyString& target_ms, const MyString& rep_ms);
    void move(MyString&& ms);
    MyString substr(const int first, const int last) const;
    int compare(const char* str) const;
    MyString operator+(const MyString& ms) const;
    MyString& operator+=(const MyString& ms);
    MyString& operator=(const MyString& ms);
    bool operator==(const char* str) const;
    bool operator!=(const char* str) const;

    void printStrAddress();

private:
    char* my_str = nullptr;
    int mystrLength = 0;
};
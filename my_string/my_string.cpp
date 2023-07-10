#include <iostream>
#include <string.h>
#include "my_string.h"
#include <list>

MyString operator+(const char* str, const MyString& ms)
{
    return MyString(str) + ms;
}

std::ostream& operator<<(std::ostream& out, const MyString& ms)
{
    out << ms.getValue() ;
    return out;
}

bool operator==(const char* str, const MyString& ms)
{
    return (ms == str);
}

bool operator!=(const char* str, const MyString& ms)
{
    return (ms != str);
}

MyString::MyString(): my_str(nullptr)
{}

MyString::MyString(const MyString& ms)
{
    if(nullptr == ms.my_str)
    {
        mystrLength = 0;
        my_str = nullptr;
    }
    else
    {
        mystrLength = ms.mystrLength;
        my_str = new char[mystrLength + 1];
        strcpy(my_str, ms.my_str);
    }
}

MyString::MyString(const char* str)
{
    if(nullptr == str)
    {
        mystrLength = 0;
        my_str = nullptr;
    }
    else
    {
        mystrLength = strlen(str);
        my_str = new char[mystrLength + 1];
        strcpy(my_str, str);
    }
}

MyString::MyString(MyString&& ms): my_str(nullptr)
{
    my_str = ms.my_str;
    ms.my_str = nullptr;
}

MyString::~MyString()
{
    delete[] my_str;
    my_str = nullptr;
}


void MyString::reverse()
{
    if(nullptr != my_str)
    {
        for(int i = 0; i < (mystrLength/2); ++i)
        {
            char temp = my_str[i];
            my_str[i] = my_str[(mystrLength-1)-i];
            my_str[(mystrLength-1)-i] = temp;
        }
    }
}

void MyString::clear()
{
    if(nullptr != my_str)
    {
        memset(&my_str, 0, mystrLength);
    }
}

void MyString::setValue(char* str)
{
    if(nullptr == str)
    {
        mystrLength = 0;
        delete[] my_str;
        my_str = nullptr;
    }
    else
    {
        mystrLength = strlen(str);
        delete[] my_str;
        my_str = new char[mystrLength + 1];
        
        strcpy(my_str, str);
    }
}

char* MyString::getValue() const
{
    return my_str;
}

char MyString::at(const int pos) const
{
    return ( 0 > pos || mystrLength <= pos)? '0' : my_str[pos];
}

char MyString::operator[](const int pos) const
{
    return at(pos);
}

void MyString::insert(const int pos, const char* str)
{
    if((nullptr != str) && (0 <= pos) && (mystrLength >= pos))
    {
        int str_length = strlen(str);
        char* new_str = new char[str_length + mystrLength + 1];

        memcpy(new_str, my_str, pos);
        memcpy(new_str+pos, str, str_length);
        memcpy(new_str+(str_length+pos), my_str+pos, mystrLength-pos);
        
        mystrLength = str_length + mystrLength;
        delete[] my_str;
        my_str = new_str;
        new_str = nullptr;
    }
}

void MyString::append(const char* str)
{
    insert(getLength(), str);
}

int MyString::find(const MyString& find_ms, const int start) const
{
    int pos = 0;
    if((nullptr == my_str) || (nullptr == find_ms.my_str))
    {
        pos = -1;
    }
    else
    {
        int find_length = find_ms.getLength();
        bool check = false;

        if((find_length > mystrLength) || (start > mystrLength))
        {
            pos = -1;
        }
        else
        {
            if(start >= 0)
            {
                for(int i = start; i < mystrLength; ++i)
                {
                    if(my_str[i] == find_ms[0])
                    {
                        check = true;

                        for(int x = 0; x < find_length; ++x)
                        {
                            if((i+x) >= mystrLength)
                            {
                                check = false;
                                break;
                            }
                            if(my_str[i+x] != find_ms[x])
                            {
                                check = false;
                                break;
                            }
                        }

                        if(check)
                        {
                            pos = i;
                            break;
                        }
                    }
                    pos = check ? i : -1;
                }
            }
        }
    }

    return pos;
}

void MyString::replace(const MyString& target_ms, const MyString& rep_ms)
{
    if((nullptr != my_str) && (nullptr != target_ms.my_str))
    {
        int match = 0;
        std::list<int> lst;

        if (getLength() >= target_ms.getLength()) 
        {
            for(int i = 0; i < mystrLength; ) 
            {
                int pos = find(target_ms, i);
                if (-1 != pos)
                {
                    ++match;
                    i = (pos + target_ms.getLength());
                    lst.push_back(pos);
                }
                else 
                {
                    ++i;
                }
            }

            if(0 != match)
            {
                char* new_str = new char[mystrLength + match * (rep_ms.getLength() - target_ms.getLength()) + 1];
                char* temp_str = my_str;
                int befor_pos = 0;
                int index = 0;

                for(int pos : lst)
                {
                    memcpy(new_str+index, temp_str, (pos - befor_pos));
                    index += (pos - befor_pos);

                    if (rep_ms.getLength() > 0) 
                    {
                        memcpy(new_str + index, rep_ms.getValue(), rep_ms.getLength());
                        index += rep_ms.getLength();
                    }
                    
                    temp_str += (pos + target_ms.getLength() - befor_pos);
                    befor_pos = (pos + target_ms.getLength());
                }

                if(nullptr != temp_str)  
                {
                    strncat(new_str, temp_str, mystrLength-befor_pos);
                }

                mystrLength = strlen(new_str);

                delete[] my_str;
                my_str = new_str;
                new_str = nullptr;
            }
        }
    }
}

void MyString::move(MyString&& ms)
{
    if(nullptr == ms.my_str)
    {
        mystrLength = 0;
        delete[] my_str;
        my_str = nullptr;
    }
    else
    {
        mystrLength = ms.getLength();
        delete[] my_str;
        my_str = ms.my_str;
        ms.my_str = nullptr;
    }
}

MyString MyString::substr(const int first, const int last) const
{
    MyString ms;

    int first_index = static_cast<unsigned int>(first);
    int last_index = static_cast<unsigned int>(last);
    int last2 = 0;
    
    if((first < last) && (first_index < mystrLength) && (first != last) && (nullptr != my_str))
    {
        last2 = (last_index > mystrLength) ? mystrLength : last;
        ms.mystrLength = last2 - first;
        ms.my_str = new char[ms.mystrLength + 1];

        memcpy(ms.my_str, my_str+first, last2 - first);
        ms.my_str[ms.mystrLength] = '\0';
    }
    else
    {
        ms.setValue(my_str);
    }

    return ms;
}

int MyString::compare(const char* str) const
{
    int check = 0;

    if((nullptr != my_str) && (nullptr == str))
    {
        check = 1;
    }
    else if((nullptr == my_str) && (nullptr != str))
    {
        check = -1;
    }
    else if((nullptr == my_str) && (nullptr == str))
    {
        check = 0;
    }
    else
    {                                                
        int i = 0;
        int str_length = strlen(str);
        int ms_length = getLength();

        if(str_length == ms_length)
        {
            while(('\0' != my_str[i]) && ('\0' != str[i]))
            {
                check = (my_str[i] == str[i]) ? 0 : ((my_str[i] > str[i]) ? 1 : -1);
                ++i;
                if(0 != check)
                {
                    break;
                }
            }
        }
        else
        {
            check = (ms_length > str_length) ? 1 : -1;
        }
    }

    return check;
}

MyString MyString::operator+(const MyString& ms) const
{
    MyString ms02 = MyString(my_str);
    ms02.append(ms.my_str);

    return ms02;
}

MyString& MyString::operator+=(const MyString& ms)
{
    append(ms.my_str);

    return *this;
} 

MyString& MyString::operator=(const MyString& ms)
{
    setValue(ms.my_str);

    return *this;
}

bool MyString::operator==(const char* str) const
{
    return 0 == compare(str);
}

bool MyString::operator!=(const char* str) const
{
    return 0 != compare(str);
}

void MyString::printStrAddress()
{
    std::cout << "&this: " << this << std::endl;
}
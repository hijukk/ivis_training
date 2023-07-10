#include <iostream>
#include <assert.h>
#include <mutex>
#include <string>

template<typename T>
class MyList
{
private:
    struct Node
    {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node() {}
        Node(const T& d) : data(d) {}
        ~Node() {}
    };

public:
    class MyIterator
    {
        friend class MyList;
    
    private:
        Node* current = nullptr;

    public:
        MyIterator() : current(nullptr){}
        MyIterator(Node* n) : current(n){}
        ~MyIterator(){}
        
    public:
        T& operator*()
        {
            return current->data;
        }

        MyIterator& operator++()
        {
            assert(nullptr != current->next);
            current = current->next;
            return *this;
        }

        MyIterator& operator--()
        {
            assert(nullptr != current->prev);
            current = current->prev;
            return *this;
        }

        bool operator==(const MyIterator& ml) const
        {
            return (current == ml.current);
        }

        bool operator!=(const MyIterator& ml) const
        {
            return (current != ml.current);
        }

    };

public:

    MyList();
    MyList(const MyList& ml);
    MyList(MyList&& ml);
    ~MyList();

public:
    inline int getSize() const
    {
        return mySize;
    }

    void assign(const MyList& ml);
    MyList& operator=(const MyList& ml);
    void push_back(const T& element);
    void push_front(const T& element);
    void pop_back();
    void pop_front();
    void insert(const MyIterator& pos, const T& element);
    bool erase(const T& element);
    void erase(MyIterator& i);
    void clear();
    
    MyIterator find(const T& element);
    bool empty() const;
    
    T front() const;
    T back() const;
    
    MyIterator begin();
    MyIterator end();

private:
    void insert_private(const MyIterator& pos, const T& element);
    bool erase_private(const T& element);
    void erase_private(MyIterator& i);
    MyIterator find_private(const T& element);
    void clear_private();

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int mySize = 0;

    std::mutex mMutex;


};

template<typename T>
MyList<T>::MyList()
{
    head = new Node;
    tail = head;
}

template<typename T>
MyList<T>::MyList(const MyList& ml)
{
    if(ml.empty())
    {
        head = new Node;
        tail = head;
    }
    else
    {
        head = new Node;
        tail = head;

        assign(ml);
    }
}

template<typename T>
MyList<T>::MyList(MyList&& ml)
{
    mySize = ml.getSize();
    std::swap(head, ml.head);
    std::swap(tail, ml.tail);   

    ml.clear();
}

template<typename T>
MyList<T>::~MyList()
{
    clear();
    delete head;
}

template<typename T>
void MyList<T>::assign(const MyList& ml)
{
    clear();

    Node *curr = ml.head;
    while(ml.tail != curr)
    {
        push_back(curr->data);
        curr = curr->next;
    }
}

template<typename T>
MyList<T>& MyList<T>::operator=(const MyList& ml)
{
    assign(ml);
    return *this;
}

template<typename T>
void MyList<T>::push_back(const T& element)
{
    mMutex.lock();

    MyIterator pos = MyIterator(tail);
    insert_private(pos, element);

    mMutex.unlock();
}

template<typename T>
void MyList<T>::push_front(const T& element)
{
    mMutex.lock();

    MyIterator pos = MyIterator(head);
    insert_private(pos, element);
    
    mMutex.unlock();
}

template<typename T>
void MyList<T>::pop_back()
{
    mMutex.lock();
    MyIterator it = MyIterator(tail);
    erase_private(--it);
    mMutex.unlock();
}  

template<typename T>
void MyList<T>::pop_front()
{
    mMutex.lock();
    MyIterator pos = MyIterator(head);
    erase_private(pos);
    mMutex.unlock();
}

template<typename T>
void MyList<T>::insert(const MyIterator& pos, const T& element)
{
    std::string log;
    log = "insert start..";
    std::cout << log << std::endl;

    mMutex.lock();
    insert_private(pos, element);
    mMutex.unlock();

    log = "insert end.." + std::to_string(element) + '\n';
    std::cout << log;
}

template<typename T>
bool MyList<T>::erase(const T& element)
{
    bool check = false;

    mMutex.lock();
    check = erase_private(element);
    mMutex.unlock();

    return check;
}

template<typename T>
void MyList<T>::erase(MyIterator& i)
{   
    int tdata = *i;
    std::cout << "erase start..." << std::to_string(tdata)<< std::endl;

    // std::cout << "========" << i.current << std::endl;
    // std::cout << "========" << begin().current << std::endl;
    // std::cout << "========" << end().current << std::endl;

    mMutex.lock();
    erase_private(i);
    mMutex.unlock();

    std::string log = "erase end.." + std::to_string(tdata) + '\n';
    std::cout << log;
}

template<typename T>
void MyList<T>::clear()
{
    mMutex.lock();
    clear_private();
    mMutex.unlock();
}

template<typename T>
typename MyList<T>::MyIterator MyList<T>::find(const T& element) 
{   
    MyIterator resNode;
    
    mMutex.lock();
    resNode = find_private(element);
    mMutex.unlock();

    return resNode;
}

template<typename T>
bool MyList<T>::empty() const
{
    return (0 == mySize);
}

template<typename T>
T MyList<T>::front() const
{
    return head->data;
}

template<typename T>
T MyList<T>::back() const
{
    T bData;

    if(nullptr != tail->prev)
    {
        bData =  tail->prev->data;
    }

    return bData;
}
    
template<typename T> 
typename MyList<T>::MyIterator MyList<T>::begin()
{
    std::unique_lock<std::mutex> lock(mMutex);

    return MyIterator(head);
}

template<typename T> 
typename MyList<T>::MyIterator MyList<T>::end()
{
    std::unique_lock<std::mutex> lock(mMutex);

    return MyIterator(tail);
}

template<typename T> 
void MyList<T>::insert_private(const MyIterator& pos, const T& element)
{
    Node* newNode = new Node(element);

    if((0 == mySize) || (head == pos.current) || (0 == pos.current->prev))
    {
        std::cout << "begin..or empty..\n";
        if (nullptr == newNode || nullptr == head) {
            std::cout << "newNode or head is nullptr. so return." << std::endl;
            return;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if(tail == pos.current)
    {
        std::cout << "end() insert..." << std::endl; 
        if (nullptr == newNode || nullptr == tail) {
            std::cout << "Error" << std::endl;
            return;
        }

        newNode->prev = tail->prev;

        if (tail->prev) {
            tail->prev->next = newNode;
        }

        newNode->next = tail;
        tail->prev = newNode;
    }
    else 
    {
        std::cout << "else insert ..\n";
        if(pos.current->prev->data)
        {
            std::cout << "else pos.current->prev->data" << std::endl;
            if(nullptr == pos.current || nullptr == newNode)
            {
                std::cout << "else Error.." << std::endl;
                return;
            }

            pos.current->prev->next = newNode;
            newNode->prev = pos.current->prev;
            newNode->next = pos.current;
            pos.current->prev = newNode;
        }
    }
    ++mySize;

}

template<typename T> 
bool MyList<T>::erase_private(const T& element)
{
    bool check = false;

    MyIterator it = find(element);

    if(MyIterator(tail) != it)
    {
        erase(it);
        check = true;
    }
    
    return check;
}

template<typename T> 
void MyList<T>::erase_private(MyIterator& i)
{
    if((!(0 == mySize)) && (i.current != tail))
    {
        if(i == MyIterator(head))
        {
            Node* temp = head->next;

            delete head;

            head = temp;
            if (nullptr != head) {
                head->prev = nullptr;
            }
        }
        else
        {
            i.current->prev->next = i.current->next;
            i.current->next->prev = i.current->prev;

            delete i.current;
            i.current = nullptr;
        }

        --mySize;
    }
}

template<typename T>
typename MyList<T>::MyIterator MyList<T>::find_private(const T& element) 
{   
    MyIterator resNode;

    std::cout << "find.." << std::endl;
    resNode = MyIterator(tail);

    if(!(0 == mySize))
    {
        for(MyIterator it = MyIterator(head); it != MyIterator(tail); ++it)
        {
            if(*it == element)
            {
                resNode = it;
                break;
            }
        }
    }

    return resNode;
}


template<typename T>
void MyList<T>::clear_private()
{
    if(!(0 == mySize))
    {
        Node* curr = head;

        while(curr != tail)
        {
            
            Node* temp = curr;
            curr = curr->next;
            delete temp;
            temp = nullptr;
        }

        head = tail;
        mySize = 0;
    }
}
#include <iostream>
#include <assert.h>

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
    void insert(const MyIterator& i, const T& element);
    void erase(const T& element);
    void erase(const MyIterator& i);
    void clear();
    
    MyIterator find(const T& element) ;
    bool empty() const;
    
    T front() const;
    T back() const;
    
    MyIterator begin();
    MyIterator end();

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int mySize = 0;

};

template<typename T>
MyList<T>::MyList()
{
    head = new Node;;
    tail = head;
}

template<typename T>
MyList<T>::MyList(const MyList& ml)
{
    if(ml.empty())
    {
        head = new Node;
        tail = head;
        mySize = 0;
    }
    else
    {
        mySize = ml.getSize();
        
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
    insert(end(), element);
}

template<typename T>
void MyList<T>::push_front(const T& element)
{
    insert(begin(), element);
}

template<typename T>
void MyList<T>::pop_back()
{
    erase(--end());
}  

template<typename T>
void MyList<T>::pop_front()
{
    erase(begin());
}

template<typename T>
void MyList<T>::insert(const MyIterator& pos, const T& element)
{
    Node* newNode = new Node(element);

    if(empty() || (pos == begin()))
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if(pos == end())
    {
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        newNode->next = tail;
        tail->prev = newNode;
    }
    else
    {
        pos.current->prev->next = newNode;
        newNode->prev = pos.current->prev;
        newNode->next = pos.current;
        pos.current->prev = newNode;
    }

    ++mySize;
}

template<typename T>
void MyList<T>::erase(const T& element)
{
    erase(find(element));
}

template<typename T>
void MyList<T>::erase(const MyIterator& i)
{
    if((!empty()) && (i.current != tail))
    {
        if(i == begin())
        {
            Node* temp = head->next;
            delete head;
            head = temp;
            head->prev = nullptr;
        }
        else
        {
            i.current->prev->next = i.current->next;
            i.current->next->prev = i.current->prev;

            delete i.current;
        }

        --mySize;
    }

}

template<typename T>
void MyList<T>::clear()
{
    if(!empty())
    {
        Node* curr = head;
        while(curr != tail)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }

        head = tail;
        mySize = 0;
    }
}

template<typename T>
typename MyList<T>::MyIterator MyList<T>::find(const T& element) 
{
    MyIterator resNode = end();

    if(!empty())
    {
        for(MyIterator it = begin(); it != end(); ++it)
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
    return MyIterator(head);
}

template<typename T> 
typename MyList<T>::MyIterator MyList<T>::end()
{
    return MyIterator(tail);
}
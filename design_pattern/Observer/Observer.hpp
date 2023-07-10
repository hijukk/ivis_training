#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
#include <mutex>

class Subject;

class IObserver
{
public:
    virtual ~IObserver() = default;

    virtual void update(int h, int w) = 0;
};

class Observer1 : public IObserver
{
public:
    virtual void update(int h, int w)
    {
        height = h;
        width = w;
        std::cout << "Observer1 start.. height = " << height << ", width = " << width << std::endl;
    }

private:
    int height;
    int width;
};

class Observer2 : public IObserver
{
public:
    virtual void update(int h, int w)
    {
        height = h;
        width = w;
        std::cout << "Observer2 start.. height = " << height << ", width = " << width << std::endl;

    }

private:
    int height;
    int width;
};

class Subject
{
public:
    virtual ~Subject(){ detachAll(); };

    virtual void attach(const std::shared_ptr<IObserver>& observ);
    virtual void detach(const std::shared_ptr<IObserver>& observ);
    virtual void detachAll();
    virtual void setNum(int h, int w);

protected:
    std::list<std::weak_ptr<IObserver>> listObserv;
    std::mutex m;

    int height;
    int width;

    virtual void notify();
};

void Subject::attach(const std::shared_ptr<IObserver>& observ)
{
    std::unique_lock<std::mutex> lock(m);

    if(nullptr != observ)
    {
        listObserv.push_back(observ);
    }
}

void Subject::detach(const std::shared_ptr<IObserver>& observ)
{
    std::unique_lock<std::mutex> lock(m);
    
    if(nullptr != observ)
    {
        for(auto it = listObserv.begin(); it != listObserv.end(); ++it)
        {
            std::shared_ptr<IObserver> wptr = it->lock();
            if(wptr == observ)
            {
                it = listObserv.erase(it);
                break;
            }    
        }
    }
}

void Subject::detachAll()
{
    std::unique_lock<std::mutex> lock(m);
    
    listObserv.clear();
}

void Subject::notify()
{
    std::unique_lock<std::mutex> lock(m);
    
    for(auto it = listObserv.begin(); it != listObserv.end(); ++it)
    {
        std::shared_ptr<IObserver> sptr = it->lock();
        if(sptr)
        {
            sptr->update(height, width);
        }
        else
        {
            it = listObserv.erase(it);
        }
    }    
}

void Subject::setNum(int h, int w)
{
    height = h;
    width = w;

    notify();
}

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <queue>
#include <semaphore.h>
#include <mutex>
#include <memory>

//g++ main.cpp -o threadsApp

#define FILENUM 3

sem_t semaphore;

int semNum = FILENUM;
std::mutex m;

bool isPrime(int num)
{
    bool check = true;

    for(int i = 2; i*i <= num; ++i)
    {
        if(0 == (num % i))
        {
            check = false;
        }
    }

    return check;
}

std::string countPrime(int tNum, int num)
{
    int count = 0;
    std::string str;

    for(int i = 2; i < num; ++i)
    {
        if(isPrime(i))
        {
            ++count;
        }
    }

    str = "thread[" + std::to_string(tNum) + "] finished. prime numbers between 0 and " + std::to_string(num) + ": " + std::to_string(count) + "\n";

    return str;
}


void writeFile(int tNum, int num, std::queue<std::shared_ptr<std::ofstream>>& filess)
{
    std::string log;
    std::string str = countPrime(tNum, num);

    sem_wait(&semaphore);

    m.lock();
    std::shared_ptr<std::ofstream> ofs = filess.front();
    filess.pop();
    m.unlock();

    *ofs << str;
    
    m.lock();
    filess.push(ofs);
    m.unlock();

    sem_post(&semaphore);
}

int main(int argc, char** argv)
{
    sem_init(&semaphore, 0, semNum);

    std::vector <std::thread> threads; 
    std::queue <std::shared_ptr<std::ofstream>> files;
    
    for (int i = 1; i <= FILENUM; i++)
    {
        files.push(std::make_shared<std::ofstream>("log" + std::to_string(i) + ".txt"));
    }

    for(int i = 1; i < argc; ++i)
    {
        threads.push_back(std::thread(writeFile, i, std::stoi(argv[i]), std::ref(files)));
    }

    for(std::thread& t : threads)
    {
        t.join();
    }

    sem_destroy(&semaphore);

    return 0;
}
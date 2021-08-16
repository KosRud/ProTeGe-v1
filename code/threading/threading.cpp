#include <thread>
#include <mutex>
#include <iostream>

#include "threading.h"

ThreadChief::ThreadChief(int thread_count, int  capacity)
{
    cores = thread_count;
    tasks_left = capacity;
    tasks = new (void(*[capacity])(void**));
    worker_threads = new std::thread[cores];
    args = new void**[tasks_left];
}

ThreadChief::~ThreadChief()
{
    for(int i = 0; i < tasks_left; i++)
        delete[] args[i];

    delete[] args;
    delete[] tasks;
    delete[] worker_threads;
}

void ThreadChief::worker()
{
    while(1)
    {
        tasks_left_access.lock();
        tasks_left --;
        int left = tasks_left;
        tasks_left_access.unlock();

        if(left < 0)
            break;

        tasks[left](args[left]);
    }
    return;
}

void ThreadChief::start()
{
    for(int i = 0; i < cores; i++)
        worker_threads[i] = std::thread(&ThreadChief::worker, this);

    for(int i = 0; i < cores; i++)
        worker_threads[i].join();
}

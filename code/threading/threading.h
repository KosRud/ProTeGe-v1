#pragma once

#include <thread>
#include <mutex>
#include <iostream>

class ThreadChief
{
private:
    int cores;
    std::thread * worker_threads;
    int tasks_left;
    std::mutex tasks_left_access;

public:
    void *** args;
    void (**tasks)(void**);

    ThreadChief(int thread_count, int  capacity);
    ~ThreadChief();

    void worker();
    void start();
};

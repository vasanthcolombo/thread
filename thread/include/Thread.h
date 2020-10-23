//
// Created by vasan on 9/8/2019.
//

#ifndef THREAD_THREAD_H
#define THREAD_THREAD_H


#include <thread>
#include <iostream>
#include <future>
using namespace std;

class Thread {
public:
    Thread(long id);
    Thread();

    virtual ~Thread() {};

    void join();

    void start();

    void stop();

    int get_id();

    bool is_stopped();

protected:
    virtual void run() = 0;

protected:
    int _id;

private:
    bool stopped;
    unique_ptr<thread> t;
};
#endif //THREAD_THREAD_H

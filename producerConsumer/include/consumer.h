//
// Created by vasan on 10/19/2019.
//
#ifndef VLIB_CONSUMER_H
#define VLIB_CONSUMER_H

#include "Thread.h"
#include "pcFW.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <sstream>

using namespace std;
using namespace VThread;

template <class T>
class PCFW;

template <class T>
class Consumer : public Thread {
public:
    Consumer(PCFW<T>& p) : mut(p.getMutex()), pipe(p.getPipe()), cond(p.getCond()) {};

protected:
    unique_ptr<T> get();
private:
    virtual void run() = 0;

private:
    shared_ptr<mutex> mut;
    shared_ptr<queue<unique_ptr<T>>> pipe;
    shared_ptr<condition_variable> cond;
};

template <class T>
unique_ptr<T> Consumer<T>::get() {
    unique_lock<mutex> lock(*mut.get());
    cond->wait(lock, [=](){return !pipe->empty();});
    unique_ptr<T> val = move(pipe->front());
    pipe->pop();
    lock.unlock();
    return move(val);
}
#endif //VLIB_CONSUMER_H

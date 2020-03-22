//
// Created by vasan on 10/6/2019.
//
#ifndef VLIB_PRODUCER_H
#define VLIB_PRODUCER_H

#include "Thread.h"
#include "pcFW.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace VThread;

template <class T>
class PCFW;

template <class T>
class Producer : public Thread {
public:
    Producer(PCFW<T>& p) : mut(p.getMutex()), pipe(p.getPipe()), cond(p.getCond()) {};

protected:
    bool put(unique_ptr<T> t);
private:
    virtual void run() = 0;

private:
    shared_ptr<mutex> mut;
    shared_ptr<queue<unique_ptr<T>>> pipe;
    shared_ptr<condition_variable> cond;
};

template <class T>
bool Producer<T>::put(unique_ptr<T> t) {
    lock_guard<mutex> lock(*mut.get());
    pipe->push(move(t));
    cond->notify_all();
    return true;
}
#endif //VLIB_PRODUCER_H

//
// Created by vasan on 10/19/2019.
//
#ifndef VLIB_CONSUMER_H
#define VLIB_CONSUMER_H

#include "Thread.h"
#include "messagePipe.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <sstream>

using namespace VThread;

template <class T>
class MessagePipe;

template <class T>
class Consumer {
public:
    Consumer(std::shared_ptr<MessagePipe<T>> p, int waitT = 5) : messagePipe(p), waitTime(waitT) {};

protected:
    std::unique_ptr<T> get();

private:
    std::shared_ptr<MessagePipe<T>> messagePipe;
    int waitTime;   // waits for this secs before checking exit status at derived class
};

template <class T>
std::unique_ptr<T> Consumer<T>::get() {
    std::unique_lock<std::mutex> lock(*messagePipe->getMutex());

    bool success = messagePipe->getCond()->wait_for(lock, std::chrono::duration<int>(std::chrono::seconds(waitTime)),
                                                    [=](){return !messagePipe->getPipe()->empty();});
    if (!success)
        return NULL;
    std::unique_ptr<T> val = move(messagePipe->getPipe()->front());
    messagePipe->getPipe()->pop();
    lock.unlock();
    return move(val);
}
#endif //VLIB_CONSUMER_H

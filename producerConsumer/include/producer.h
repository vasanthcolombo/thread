//
// Created by vasan on 10/6/2019.
//
#ifndef VLIB_PRODUCER_H
#define VLIB_PRODUCER_H

#include "Thread.h"
#include "messagePipe.h"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template <class T>
class MessagePipe;

template <class T>
class Producer {
public:
    Producer(std::shared_ptr<MessagePipe<T>> p) : messagePipe(p) {};
    Producer() {
        messagePipe = std::make_shared<MessagePipe<T>>();
    };

protected:
    bool put(unique_ptr<T> t);
    std::shared_ptr<MessagePipe<T>> getMessagePipe();

private:
    std::shared_ptr<MessagePipe<T>> messagePipe;
};

template <class T>
bool Producer<T>::put(unique_ptr<T> t) {
    lock_guard<std::mutex> lock(*messagePipe->getMutex());
    messagePipe->getPipe()->push(move(t));
    messagePipe->getCond()->notify_all();
    return true;
}
#endif //VLIB_PRODUCER_H

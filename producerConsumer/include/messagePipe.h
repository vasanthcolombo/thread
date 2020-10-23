//
// Created by vasan on 10/19/2019.
//

#ifndef VLIB_MESSAGEPIPE_H
#define VLIB_MESSAGEPIPE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include "Thread.h"
#include "consumer.h"
#include "producer.h"

using namespace VThread;

template <class T>
class MessagePipe {
public:
    MessagePipe();

private:
    std::shared_ptr<std::queue<std::unique_ptr<T>>> pipe;
    std::shared_ptr<std::mutex> mut;
    std::shared_ptr<std::condition_variable> cond;

public:
    std::shared_ptr<queue<std::unique_ptr<T>>> getPipe();
    std::shared_ptr<std::mutex> getMutex();
    std::shared_ptr<std::condition_variable> getCond();


};

template <class T>
MessagePipe<T>::MessagePipe() {
    mut = make_shared<std::mutex>();
    pipe = make_shared<std::queue<std::unique_ptr<T>>>();
    cond = make_shared<std::condition_variable>();
    cout << "creating producer consumer framework" << endl;
}

template <class T>
std::shared_ptr<std::condition_variable> MessagePipe<T>::getCond() {
    return cond;
}

template <class T>
std::shared_ptr<mutex> MessagePipe<T>::getMutex() {
    return mut;
}

template <class T>
std::shared_ptr<std::queue<std::unique_ptr<T>>> MessagePipe<T>::getPipe() {
    return pipe;
}
#endif //VLIB_MESSAGEPIPE_H


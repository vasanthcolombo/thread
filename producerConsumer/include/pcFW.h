//
// Created by vasan on 10/19/2019.
//

#ifndef VLIB_PRODUCERCONSUMER_H
#define VLIB_PRODUCERCONSUMER_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include "Thread.h"
#include "consumer.h"
#include "producer.h"

using namespace std;
using namespace VThread;

template <class T>
class PCFW {
public:
    PCFW();

private:
    shared_ptr<queue<unique_ptr<T>>> pipe;
    shared_ptr<mutex> mut;
    shared_ptr<condition_variable> cond;

public:
    shared_ptr<queue<unique_ptr<T>>> getPipe();
    shared_ptr<mutex> getMutex();
    shared_ptr<condition_variable> getCond();


};

template <class T>
PCFW<T>::PCFW() {
    mut = make_shared<mutex>();
    pipe = make_shared<queue<unique_ptr<T>>>();
    cond = make_shared<condition_variable>();
    cout << "creating producer consumer framework" << endl;
}

template <class T>
shared_ptr<condition_variable> PCFW<T>::getCond() {
    return cond;
}

template <class T>
shared_ptr<mutex> PCFW<T>::getMutex() {
    return mut;
}

template <class T>
shared_ptr<queue<unique_ptr<T>>> PCFW<T>::getPipe() {
    return pipe;
}
#endif //VLIB_PRODUCERCONSUMER_H


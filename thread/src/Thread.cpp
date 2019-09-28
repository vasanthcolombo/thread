//
// Created by vasan on 9/8/2019.
//

#include "Thread.h"
using namespace VThread;

Thread::Thread(int id) : _id(id){
    stopped = true;
}
void Thread::start() {
    stopped = false;
    t = make_unique<thread>(&Thread::run, this);
}

void Thread::stop() {
    stopped = true;
}
void Thread::join() {
    t->join();
}

int Thread::get_id() {
    return _id;
}

bool Thread::is_stopped() {
    return stopped;
}
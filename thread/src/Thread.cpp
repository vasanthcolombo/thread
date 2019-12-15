//
// Created by vasan on 9/8/2019.
//

#include "Thread.h"
#include <sstream>

using namespace VThread;

Thread::Thread(long id) : _id(id){
    stopped = true;
}

Thread::Thread() {
    std::stringstream ss;
    ss << this_thread::get_id();
    _id = stol(ss.str());
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
//
// Created by vasan on 3/22/2020.
//
#include "logger.h"
#include <thread>
#include <unistd.h>

void func1() {
    Logger log;
    for (int i = 0; i < 100; ++i) {
        std::string line = "func1: " + std::to_string(i);
        log.log(Logger::DEBUG, line);
    }
}

void func2() {
    Logger log;
    for (int i = 0; i < 100; ++i) {
        std::string line = "func2: " + std::to_string(i);
        log.log(Logger::INFO, line);
    }
}

int main() {
    Logger::createLogger(Logger::INFO, "G:\\Study\\Repo\\vlib\\util\\a.txt");
    //Logger::createLogger(Logger::INFO);

    Logger log;
    thread t1(func1);
    thread t2(func2);

    t1.join();
    t2.join();
}

//
// Created by vasan on 3/22/2020.
//
#include <string>
#include <iostream>
#include "logger.h"

std::string Level[] = {
        [Logger::TRACE] = "TRACE: ",
        [Logger::DEBUG] = "DEBUG: ",
        [Logger::INFO] = "INFO: ",
        [Logger::WARN] = "WARN: ",
        [Logger::ERR] = "ERR: ",
        [Logger::FTL] = "FTL: "
};

std::queue<std::pair<Logger::LogLevel, std::string>> Logger::logMessages;
std::mutex Logger::mutex;
std::condition_variable Logger::condition;
Logger::LogLevel Logger::logLevel;
unique_ptr<std::ostream> Logger::out;
Logger::State Logger::state = Logger::STOPPED;
std::unique_ptr<std::thread> Logger::thd;
int Logger::numOfInstances = 0;
int Logger::sleepTimerInSecs = 10;

Logger::Logger() {
    numOfInstances++;
}

Logger::~Logger() {
    if (--numOfInstances == 0) {
        out->flush();
        state = STOP;
        thd->join();
    }
}

void Logger::createLogger(Logger::LogLevel level, std::string logFileName) {
    logLevel = level;
     out = std::make_unique<std::ofstream>(logFileName);
    if (!dynamic_cast<std::ofstream*>(out.get())->is_open()) {
        std::string error = "Unable to open the file " + logFileName;
        throw std::runtime_error(error);
    }
    thd = make_unique<std::thread>(&Logger::run);
    state = RUNNING;
}

void Logger::createLogger(Logger::LogLevel level) {
    logLevel = level;
    out.reset(&std::cout);
    thd = make_unique<std::thread>(&Logger::run);
    state = RUNNING;
}

void Logger::log(LogLevel level, std::string& text) {
    std::lock_guard<std::mutex> lock(mutex);
    logMessages.push(std::pair<LogLevel,std::string>(level, text));
    condition.notify_all();
}

void Logger::log(LogLevel logLevel, const char* text) {
    std::string str(text);
    log(logLevel, str);
}

void Logger::run() {
    bool success = true;
    while(state == RUNNING || success == true) {
        std::unique_lock<std::mutex> lock(mutex);
        success = condition.wait_for(lock, std::chrono::duration<int>(std::chrono::seconds(sleepTimerInSecs)),
                                          [](){return !logMessages.empty();});
        if (!success)
            continue;
        auto pair = logMessages.front();
        logMessages.pop();
        lock.unlock();

        if (pair.first >= logLevel) {
            *out << Level[pair.first] + pair.second << endl;
        }
    }
}

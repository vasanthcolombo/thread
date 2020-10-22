//
// Created by vasan on 3/22/2020.
//

#ifndef VLIB_LOGGER_H
#define VLIB_LOGGER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include "Thread.h"

class Logger {
public:
    enum LogLevel {
        TRACE = 0,
        DEBUG,
        INFO,
        WARN,
        ERR,
        FTL
    };

    enum State {
        RUNNING,
        STOP,
        STOPPED
    };

private:
    static std::queue<std::pair<LogLevel, std::string>> logMessages;
    static std::mutex mutex;
    static std::condition_variable condition;
    static LogLevel logLevel;
    static unique_ptr<std::ostream> out;
    static State state;
    static std::unique_ptr<std::thread> thd;
    static int numOfInstances;
    static int sleepTimerInSecs;

public:
    Logger();
    virtual  ~Logger();
    static void createLogger(LogLevel level, std::string logFileName);
    static void createLogger(LogLevel level);
    static void destroyLogger();
    void log(LogLevel logLevel, std::string text);
    void log(LogLevel logLevel, const char *text);

private:
    static void run();
};
#endif //VLIB_LOGGER_H

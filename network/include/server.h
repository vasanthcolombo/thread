//
// Created by vasan on 10/15/2020.
//

#ifndef VLIB_SERVER_H
#define VLIB_SERVER_H

#include "configReader.h"
#include "serverSession.h"
#include "logger.h"

class Server {
public:
    Server(ConfigReader& configReader);
    void start();
    void waitToFinish();

private:
    std::vector<ServerSession> sessions;
    Logger logger;
};
#endif //VLIB_SERVER_H

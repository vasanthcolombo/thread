//
// Created by vasan on 10/13/2020.
//

#ifndef VLIB_CLIENT_H
#define VLIB_CLIENT_H

#include "configReader.h"
#include "clientSender.h"
#include "logger.h"

class Client {
public:
    Client(ConfigReader& configReader);
    void start();
    void waitToFinish();

private:
    std::vector<ClientSender> senders;
    Logger logger;
};
#endif //VLIB_CLIENT_H

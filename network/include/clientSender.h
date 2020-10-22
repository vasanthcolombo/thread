//
// Created by vasan on 10/8/2020.
//
#ifndef VLIB_CLIENTSENDER_H
#define VLIB_CLIENTSENDER_H

#include "clientSocket.h"
#include "fileReader.h"
#include "logger.h"
#include "configReader.h"
#include "networkConfigReader.h"
#include <memory>
#include <thread>

class ClientSender {
public:
    ClientSender(const ConfigReader& config, int id);
    ClientSender(ClientSender&&) = default;
    virtual ~ClientSender();
    bool start();
    void run();
    void waitToFinish();

private:
    ConfigReader configReader_;
    int id_;
    std::string idName_;
    Logger logger;
    std::unique_ptr<ClientSocket> socket_;
    std::unique_ptr<FileReader> fileReader_;
    std::unique_ptr<std::thread> thd_;
};
#endif //VLIB_CLIENTSENDER_H

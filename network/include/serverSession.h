//
// Created by vasan on 10/20/2020.
//

#ifndef VLIB_SERVERSESSION_H
#define VLIB_SERVERSESSION_H

#include "configReader.h"
#include "serverSocket.h"
#include "networkConfigReader.h"
#include "logger.h"
#include <memory>

class ServerSession {
public:
    ServerSession(const ConfigReader& configReader, int id);
    ~ServerSession();
    ServerSession(ServerSession&&) = default;
    bool start();
    void waitToFinish();
    int getSupportedConnections();

private:
    void run(int threadNum);
private:
    std::unique_ptr<ServerSocket> socket_;
    std::vector<std::thread> vec_thd_;
    ConfigReader configReader_;
    int id_;
    std::string idName_;
    Logger logger;
    int numConnsPerSession;
};
#endif //VLIB_SERVERSESSION_H

//
// Created by vasan on 10/2/2020.
//

#ifndef VLIB_SERVERSOCKET_H
#define VLIB_SERVERSOCKET_H

#include "socket.h"
#include "logger.h"

struct ConnectedClientInfo {
    std::string clientIp;
    std::string port;
};

class ServerSocket : public Socket {
public:
    ServerSocket(std::string src_ip, int port);
    int waitForConnection(ConnectedClientInfo& connectedClientInfo);

private:
    Logger logger;
    //std::vector<int> dataSockets;       // holds data sockets of all accepted connections
    //std::vector<std::unique_ptr<std::thread>> dataThreads;   // data read write threads for each accepted connection
};
#endif //VLIB_SERVERSOCKET_H

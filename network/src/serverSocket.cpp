//
// Created by vasan on 10/2/2020.
//

#include <cygwin/socket.h>
#include <stdexcept>
#include <sys/socket.h>
#include <cygwin/in.h>
#include <strings.h>
#include <cstring>
#include <arpa/inet.h>
#include "serverSocket.h"

ServerSocket::ServerSocket(std::string src_ip, int port) : Socket(src_ip, port) {}

int ServerSocket::waitForConnection() {
    ::listen(sockID, 5);
    struct sockaddr_in clientadd;
    bzero(&clientadd, sizeof(sockaddr_in));

    socklen_t clientLen = sizeof(sockaddr_in);
    int connectedSockID = ::accept(sockID, (struct sockaddr*)&clientadd, &clientLen);
    if (connectedSockID < 0) {
        throw std::runtime_error("Error while accepting connection, returned value: " + std::to_string(connectedSockID) + ", error: " + strerror(errno));
    }
    logger.log(Logger::INFO, "Accepted connection from " + (std::string)inet_ntoa(clientadd.sin_addr) + ":" + std::to_string(ntohs(clientadd.sin_port)));
    return connectedSockID;
}
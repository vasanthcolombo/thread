//
// Created by vasan on 10/2/2020.
//

#include <stdexcept>
#include <cygwin/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include "clientSocket.h"

ClientSocket::ClientSocket(std::string src_ip, int src_port) : Socket(src_ip, src_port) {}

bool ClientSocket::connect(std::string dst_ip, int dst_port) {
    struct sockaddr_in serveradd;
    bzero(&serveradd, sizeof(sockaddr_in));

    serveradd.sin_addr.s_addr = inet_addr(dst_ip.c_str());
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(dst_port);

    int ret = ::connect(sockID, (struct sockaddr*)&serveradd, sizeof(serveradd));
    if (!ret)
        return true;
    else
        return false;
}
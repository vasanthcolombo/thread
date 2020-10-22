//
// Created by vasan on 10/2/2020.
//

#include <strings.h>
#include <cygwin/in.h>
#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include "socket.h"

Socket::Socket(std::string src_ip, int prt) : srcIP(src_ip), port(prt) {
    sockID = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servadd;
    bzero(&servadd, sizeof(sockaddr_in));

    servadd.sin_addr.s_addr = inet_addr(src_ip.c_str());
    servadd.sin_family = AF_INET;
    servadd.sin_port = htons(port);
    int ret;
    if ((ret = bind(sockID, (struct sockaddr*)&servadd, sizeof(servadd))) <= -1) {
        throw std::runtime_error("unable to bind socket at " + src_ip + ":" + std::to_string(port) + ", returned value: " + std::to_string(ret) + ", error: " + strerror(errno));
    }
}

bool Socket::send(const std::string &line) {
    int lenToSend = line.length();
    int lenSent = 0;
    int ret;
    do {
        std::string strToSend = line.substr(lenSent);
        if ((ret = ::send(sockID, strToSend.c_str(), strToSend.length(), 0)) < 0) {
            throw std::runtime_error("Unexpected error while sending data through sock id: " + std::to_string(sockID) + ", returned value: " + std::to_string(ret) + ", error: " + strerror(errno));
        }
        lenSent += ret;
    } while (lenToSend > lenSent);
    return true;
}

bool Socket::receive(int listeningSocket, std::string &line) {
    int maxLength = 1000;
    char bytes[maxLength];

    int ret = recv(listeningSocket, bytes, maxLength, 0);
    if (ret > 0) {
        line = bytes;
        return true;
    }
    else if (ret == 0) {
        return false;   // orderly shutdown from peer
    }
    else {
        throw std::runtime_error("Unexpected error while reading from sock id: " + std::to_string(sockID) + ", returned value: " + std::to_string(ret) + ", error: " + strerror(errno));
    }
}

void Socket::close() {
    ::close(sockID);
}

int Socket::getSockID() {
    return sockID;
}
//
// Created by vasan on 9/30/2020.
//

#ifndef VLIB_SOCKET_H
#define VLIB_SOCKET_H

#include <string>

class Socket {
public:
    Socket(std::string src_ip, int prt);
    Socket& operator=(Socket&& socket) = default;
    bool send(const std::string& line);
    bool receive(int listeningSocket, std::string& line);
    void close();
    virtual int getSockID();
protected:
    int sockID;

private:
    std::string srcIP;
    int port;
};

#endif //VLIB_SOCKET_H

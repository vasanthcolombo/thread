//
// Created by vasan on 10/2/2020.
//

#ifndef VLIB_CLIENTSOCKET_H
#define VLIB_CLIENTSOCKET_H

#include "socket.h"

class ClientSocket : public Socket {
public:
    ClientSocket(std::string src_ip, int src_port);
    bool connect(std::string dst_ip, int dst_port);
};
#endif //VLIB_CLIENTSOCKET_H

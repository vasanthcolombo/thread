//
// Created by vasan on 10/20/2020.
//

#include <algorithm>
#include "serverSession.h"
#include "util.h"

ServerSession::ServerSession(const ConfigReader &configReader, int id) :
        configReader_(configReader),
        id_(id),
        idName_("[Session " + std::to_string(id_) + "] ") {
    std::string srcIp = configReader_.get(NetworkConfigReader::SRC_IP);
    int port = configReader_.getUnsignedInt(NetworkConfigReader::SRC_PORT);
    if (!srcIp.empty() && port != UNDEFINED_INT) {
        socket_ = std::make_unique<ServerSocket>(srcIp, port);
        logger.log(Logger::INFO, idName_ + "Session created with source ip: " + srcIp + ", source port: " + std::to_string(port));

        numConnsPerSession = configReader_.getUnsignedInt(NetworkConfigReader::NUM_CONNS) != UNDEFINED_INT ? configReader_.getUnsignedInt(NetworkConfigReader::NUM_CONNS) : 1;
        logger.log(Logger::INFO, idName_ + "Session accepts " + std::to_string(numConnsPerSession) + " simultaneous connections");
    }
    else {
        std::string errorStr = idName_ + "Invalid source ip: " + srcIp + " or port: " + std::to_string(port) + " for server reader id: " + std::to_string(id_);
        logger.log(Logger::FTL, errorStr);
        throw std::runtime_error(errorStr);
    }
}

ServerSession::~ServerSession() {
    socket_->close();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

bool ServerSession::start() {
    int threadId = vec_thd_.size();
    vec_thd_.emplace_back(&ServerSession::run, this, threadId);
}

void ServerSession::run(int threadNum) {
    int dataSocket;
    std::string printStr;
    printStr = idName_ + "[thd " + std::to_string(threadNum) + "] ";

    try {
        ConnectedClientInfo connectedClientInfo;
        dataSocket = socket_->waitForConnection(connectedClientInfo);
        logger.log(Logger::INFO, printStr + "Accepted connection from " + connectedClientInfo.clientIp+ ":"
            + connectedClientInfo.port);
    }
    catch (std::exception& e) {
        logger.log(Logger::FTL, printStr + "Unable to start server reader due to " + e.what());
        abort();
    }

    std::string line;
    try {
        logger.log(Logger::DEBUG, printStr + "waiting for data");
        while (socket_->receive(dataSocket, line)) {
            logger.log(Logger::INFO, printStr + "Received line: " + line );
            line.clear();
        }
        logger.log(Logger::INFO, printStr + "Peer closed connection gracefully");
    }
    catch (std::exception& e) {
        logger.log(Logger::ERR, printStr + "Unexpected termination due to " + e.what());
    }
}

void ServerSession::waitToFinish() {
    for_each(vec_thd_.begin(), vec_thd_.end(), [](std::thread& thd){thd.join();});
}

int ServerSession::getSupportedConnections() {
    return numConnsPerSession;
}
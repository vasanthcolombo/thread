//
// Created by vasan on 10/15/2020.
//

#include "server.h"
#include "logger.h"
#include <algorithm>

Server::Server(ConfigReader &configReader) {
    int noOfSessions = configReader.getSegmentCount();
    sessions.reserve(noOfSessions);

    for (int i = 0; i < noOfSessions; ++i) {
        try {
            sessions.emplace_back(configReader.getConfigReader(i), i + 1);
        }
        catch (std::exception& e) {
            logger.log(Logger::FTL, "Session creation failed with " + (std::string)e.what());
            abort();
        }
    }
    logger.log(Logger::INFO, " Server created with " + std::to_string(noOfSessions) + " sessions");
}

void Server::start() {
    std::for_each(sessions.begin(), sessions.end(), [](ServerSession& session) {
        for (int i = 0; i < session.getSupportedConnections(); ++i)
            session.start();    // each will trigger the socket to listen on a different thread
    });
}

void Server::waitToFinish() {
    std::for_each(sessions.begin(), sessions.end(), [](ServerSession& session){session.waitToFinish();});
}
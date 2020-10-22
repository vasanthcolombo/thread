//
// Created by vasan on 10/19/2020.
//

#include "logger.h"
#include "server.h"

int main(int argc, char* argv[]) {
    std::string lines = "("
                        "SRC_IP = 192.168.0.147 \n"
                        "SRC_PORT = 20000 \n"
                        ")";
    Logger::createLogger(Logger::DEBUG);
    Logger logger;
    std::string configFile;
    std::unique_ptr<Server> server;

    try {
        if (argc > 1) {
            configFile = argv[1];
            ConfigReader configReader(configFile);
            server = std::make_unique<Server>(configReader);
        } else {
            ConfigReader configReader(lines);
            server = std::make_unique<Server>(configReader);
        }
    }
    catch (std::exception& e) {
        logger.log(Logger::FTL, "Unable to create config reader: " + (std::string)e.what());
        abort();
    }
    logger.log(Logger::INFO, "Starting server");
    server->start();
    server->waitToFinish();
    logger.log(Logger::INFO, "Stopped server");

    return 0;
}
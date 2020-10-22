//
// Created by vasan on 10/15/2020.
//
#include "client.h"
#include "logger.h"
/*
 * arg 1: data file
 * arg 2: config file (optional)
 */
int main(int argc, char* argv[]) {
    std::string lines = "("
                        "SRC_IP = 192.168.0.147 \n"
                        "SRC_PORT = 10000 \n"
                        "DEST_IP = 192.168.0.147 \n"
                        "DEST_PORT = 20000 \n"
                        "READ_FROM_MEM = true \n"
                        "READ_FILE_NAME = client.txt \n"
                        "ASCII_TO_BINARY_CONV = false \n"
                        "MEM_READ_LINES = 10000 \n"
                        "BURST_INTERVAL_SEC = 1 \n"
                        "LINES_SENT_IN_BURST = 1"
                        ")";
    Logger::createLogger(Logger::DEBUG);
    Logger logger;
    std::string configFile;
    std::unique_ptr<Client> client;
    try {
        if (argc > 1) {
            configFile = argv[1];
            ConfigReader configReader(configFile);
            client = std::make_unique<Client>(configReader);
        } else {
            ConfigReader configReader(lines);
            client = std::make_unique<Client>(configReader);
        }
    }
    catch (std::exception& e) {
        logger.log(Logger::FTL, "Unable to create config reader: " + (std::string)e.what());
        abort();
    }

    logger.log(Logger::INFO, "Starting client");
    client->start();

    client->waitToFinish();
    logger.log(Logger::INFO, "Stopped client");


    return 0;
}

//
// Created by vasan on 10/13/2020.
//

#include "client.h"
#include "logger.h"
#include <algorithm>

Client::Client(ConfigReader &configReader) {
    int noOfClients = configReader.getSegmentCount();
    senders.reserve(noOfClients);

    for (int i = 0; i < noOfClients; ++i) {
        try {
            senders.emplace_back(configReader.getConfigReader(i), i + 1);
        }
        catch (std::exception& e) {
            logger.log(Logger::FTL, "Sender creation failed with " + (std::string)e.what());
            abort();
        }
    }
    logger.log(Logger::INFO, " client with " + std::to_string(noOfClients) + " senders operating on individual threads created");
}

void Client::start() {
    std::for_each(senders.begin(), senders.end(), [](ClientSender& sender){sender.start();});
}

void Client::waitToFinish() {
    std::for_each(senders.begin(), senders.end(), [](ClientSender& sender){sender.waitToFinish();});
}
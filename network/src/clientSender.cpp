//
// Created by vasan on 10/8/2020.
//
#include "clientSender.h"
#include "util.h"
#include "memoryFileReader.h"
#include "diskFileReader.h"
#include <string>
#include <thread>
#include <unistd.h>

ClientSender::ClientSender(const ConfigReader& config, int id) :
    configReader_(config),
    id_(id),
    idName_("[Sender " + std::to_string(id_) + "] ") {
    std::string srcIp = configReader_.get(NetworkConfigReader::SRC_IP);
    int port = configReader_.getUnsignedInt(NetworkConfigReader::SRC_PORT);
    if (!srcIp.empty() && port != UNDEFINED_INT) {
        socket_ = std::make_unique<ClientSocket>(srcIp, port);
    }
    else {
        std::string errorStr = idName_ + "Invalid source ip: " + srcIp + " or port: " + std::to_string(port) + " for client sender id: " + std::to_string(id_);
        logger.log(Logger::FTL, errorStr);
        throw std::runtime_error(errorStr);
    }

    try {
        if (configReader_.getBool(NetworkConfigReader::READ_FROM_MEM)) {
            fileReader_ = std::make_unique<MemoryFileReader>(configReader_.get(NetworkConfigReader::READ_FILE_NAME),
                                                             configReader_.getBool(
                                                                     NetworkConfigReader::ASCII_TO_BINARY_CONV),
                                                             (configReader_.getUnsignedInt(
                                                                     NetworkConfigReader::MEM_READ_LINES) ==
                                                              UNDEFINED_INT) ? 10000 : configReader_.getUnsignedInt(
                                                                     NetworkConfigReader::MEM_READ_LINES));
        } else {
            fileReader_ = std::make_unique<DiskFileReader>(configReader_.get(NetworkConfigReader::READ_FILE_NAME),
                                                             configReader_.getBool(NetworkConfigReader::ASCII_TO_BINARY_CONV));
        }
    }
    catch (std::exception e) {
        std::string errStr = idName_ + "Unable to create reader associated with file: " + configReader_.get(NetworkConfigReader::READ_FILE_NAME)
                + ", error: " + e.what();
        logger.log(Logger::FTL, errStr);
        abort();
    }
}

ClientSender::~ClientSender() {
    socket_->close();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

bool ClientSender::start() {
    std::string destIp = configReader_.get(NetworkConfigReader::DEST_IP);
    int destPort = configReader_.getUnsignedInt(NetworkConfigReader::DEST_PORT);

    if (destIp.empty() || destPort == UNDEFINED_INT) {
        logger.log(Logger::ERR, (idName_ + "Invalid IP " + destIp + " or port " + std::to_string(destPort)));
        return false;
    }
    if (socket_->connect(destIp, destPort)) {
        logger.log(Logger::INFO, idName_ + "Connected to destination " + destIp + ":" + std::to_string(destPort));
        thd_ = std::make_unique<std::thread>(&ClientSender::run, this);
        return true;
    }
    else {
        logger.log(Logger::ERR, idName_ + "Unable to connect to destination " + destIp + ":" + std::to_string(destPort));
        return false;
    }
}

void ClientSender::run() {
    logger.log(Logger::DEBUG, idName_ + "Starting to send data");
    std::string line;
    int linesInBurst = 0;
    int linesSent = 0;
    std::chrono::duration<long, std::nano> nanos = std::chrono::duration<long, std::nano> (
            (configReader_.getUnsignedLong(NetworkConfigReader::BURST_INTERVAL_SEC) != UNDEFINED_LONG ?
            configReader_.getUnsignedLong(NetworkConfigReader::BURST_INTERVAL_SEC) : 0) * 1000000000
                    +
            configReader_.getUnsignedLong(NetworkConfigReader::BURST_INTERVAL_NANOS) != UNDEFINED_LONG ?
            configReader_.getUnsignedLong(NetworkConfigReader::BURST_INTERVAL_NANOS) : 0);

    while (fileReader_->getNextLine(line)) {
        if (nanos.count() && linesInBurst >= configReader_.getUnsignedInt(NetworkConfigReader::LINES_SENT_IN_BURST)) {
            std::this_thread::sleep_for(nanos);
            linesInBurst = 0;
        }
        bool sent = socket_->send(line);
        if (sent) {
            logger.log(Logger::DEBUG, idName_ + "Sent line no: " + std::to_string(linesSent++ + 1) +
            ", line: " + line);
            linesInBurst++;
        }
        else
            logger.log(Logger::ERR, idName_ + "error while trying to send data");
    }
    logger.log(Logger::INFO, idName_ + "Done sending all lines in file");
}

void ClientSender::waitToFinish() {
    thd_->join();
}
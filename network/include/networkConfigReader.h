//
// Created by vasan on 10/8/2020.
//

#ifndef VLIB_NETWORKCONFIGREADER_H
#define VLIB_NETWORKCONFIGREADER_H

#include "configReader.h"

class NetworkConfigReader : ConfigReader {
public:
    static const std::string SRC_IP;
    static const std::string SRC_PORT;
    static const std::string DEST_IP;
    static const std::string DEST_PORT;
    static const std::string READ_FROM_MEM;
    static const std::string READ_FILE_NAME;
    static const std::string ASCII_TO_BINARY_CONV;
    static const std::string MEM_READ_LINES;
    static const std::string BURST_INTERVAL_SEC;
    static const std::string BURST_INTERVAL_NANOS;
    static const std::string LINES_SENT_IN_BURST;

};

#endif //VLIB_NETWORKCONFIGREADER_H

#ifndef __JSON_READER_H__
#define __JSON_READER_H__

#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>
#include "json.hpp"
#include "user.hpp"

using json = nlohmann::json;

const std::string NOT_QUANTIFIED_STR = "-";
const int NOT_QUANTIFIED_INT = -1;

class JsonReader
{
public:
    JsonReader(const std::string& config_path);
    int getCommandChannelPort();
    std::string getHostName();
    
private:
    void read(const std::string& config_path);

    int commandChannelPort;
    std::string hostName;
    void readConfig(json j_config);
};

#endif
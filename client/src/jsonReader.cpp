#include "../include/jsonReader.hpp"

JsonReader::JsonReader(const std::string& config_path)
{
    read(config_path);
}

void JsonReader::read(const std::string& config_path)
 {
    std::ifstream f1(config_path);
    json j_config;
    f1 >> j_config;

    readConfig(j_config);
}

void JsonReader::readConfig(json j_config)
{
    commandChannelPort = j_config["commandChannelPort"];
    hostName = j_config["hostName"];
}


int JsonReader::getCommandChannelPort()
{ return commandChannelPort; }

std::string JsonReader::getHostName()
{ return hostName; }
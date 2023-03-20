#include "logger.hpp"

Logger::Logger()
{
    outFile.open("log.txt", std::ios::app);
}

void Logger::writeMessage(std::string message)
{
    outFile << message << "\n";
}
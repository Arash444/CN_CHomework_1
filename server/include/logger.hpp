#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <fstream>

class Logger
{
public:
    Logger();
    void writeMessage(std::string message);
private:
    std::ofstream outFile;
};

#endif
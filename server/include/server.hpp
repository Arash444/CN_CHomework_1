#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>
#include "jsonReader.hpp"
#include <string>
#include "Date.hpp"
#include "termcolor.hpp"

class Server
{
public:
    Server(const std::string& config_path,
            const std::string& rooms_path,
            const std::string& user_info_path);
    void run();

private:
    JsonReader jsonReader;
    int commandChannelPort;
    std::string hostName;
    std::vector<User*> allUsers;
    std::vector<Room*> allRooms; 
    Date CurrentDate;

    void setServerDate(void);
};

#endif
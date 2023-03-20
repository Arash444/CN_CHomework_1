#include "../include/jsonReader.hpp"

JsonReader::JsonReader(const std::string& config_path,
 const std::string& rooms_path,
 const std::string& user_info_path
)
{
    read(config_path, rooms_path, user_info_path);
}

void JsonReader::read(const std::string& config_path,
 const std::string& rooms_path,
 const std::string& user_info_path) 
 {
    std::ifstream f1(config_path), f2(rooms_path), f3(user_info_path);
    json j_config, j_rooms, j_user;
    f1 >> j_config;
    f2 >> j_rooms;
    f3 >> j_user;

    readConfig(j_config);
    readRoomsInfo(j_rooms);
    readUserInfo(j_user);
}

void JsonReader::readConfig(json j_config)
{
    commandChannelPort = j_config["commandChannelPort"];
    hostName = j_config["hostName"];
}

void JsonReader::readRoomsInfo(json j_rooms)
{
    for (auto& room: j_rooms["rooms"])
    {
        int number = stoi(room["number"].get<std::string>());
        int status = room["status"].get<int>();
        int price = room["price"].get<int>();
        int maxCapacity = room["maxCapacity"].get<int>();
        int capacity = room["capacity"].get<int>();
        std::vector<User*> roomUsers = {};
        for (auto& userInRoom: room["users"])
        {
            int id = userInRoom["id"];
            std::string username = NOT_QUANTIFIED_STR;
            std::string password = NOT_QUANTIFIED_STR;
            bool is_admin = false;
            std::string purse = NOT_QUANTIFIED_STR;
            std::string phoneNumber = NOT_QUANTIFIED_STR;
            std::string address = NOT_QUANTIFIED_STR;
            int numOfBeds = userInRoom["numOfBeds"];
            std::string reserveDate = userInRoom["reserveDate"];
            std::string checkoutDate = userInRoom["checkoutDate"];
            int userRoomNum = number;

            roomUsers.push_back(new User(id, username, password, 
            is_admin, purse, phoneNumber, address, numOfBeds, 
            reserveDate, checkoutDate, userRoomNum));
        }
        allRooms.push_back(new Room(number, status, price,
         maxCapacity, capacity, roomUsers));
    }
}

void JsonReader::readUserInfo(json j_user)
{
    for (auto& user: j_user["users"])
    {
        int id = user["id"].get<int>();
        std::string username = user["user"].get<std::string>();
        std::string password = user["password"].get<std::string>();
        bool is_admin = user["admin"].get<std::string>() == "true";
        std::string purse = NOT_QUANTIFIED_STR;
        std::string phoneNumber = NOT_QUANTIFIED_STR;
        std::string address = NOT_QUANTIFIED_STR;
        int numOfBeds = NOT_QUANTIFIED_INT;
        std::string reserveDate = NOT_QUANTIFIED_STR;
        std::string checkoutDate = NOT_QUANTIFIED_STR;
        int userRoomNum = NOT_QUANTIFIED_INT;
        if(!is_admin)
        {
            purse = user["purse"].get<std::string>();
            phoneNumber = user["phoneNumber"].get<std::string>();
            address = user["address"].get<std::string>();
        }
        User* newUser = new User(id, username, password, is_admin,
         purse, phoneNumber, address, numOfBeds, 
         reserveDate, checkoutDate, userRoomNum);
        allUsers.push_back(newUser);
    }
}

int JsonReader::getCommandChannelPort()
{ return commandChannelPort; }

std::string JsonReader::getHostName()
{ return hostName; }

std::vector<User*> JsonReader::getUsers()
{ return allUsers; }

std::vector<Room*> JsonReader::getRooms()
{ return allRooms; }

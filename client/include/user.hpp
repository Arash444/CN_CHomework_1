#ifndef __USER_H__
#define __USER_H__

#include <string>

class User
{
public:
    User(
        const int& id,
        const std::string& username,
        const std::string& password,
        const bool& isAdmin,
        const std::string& purse,
        const std::string& phoneNumber,
        const std::string& address,
        const int& numOfBeds,
        std::string& reserveDate,
        std::string& checkoutDate,
        const int& userRoomNum
    );

    int id;
    std::string username;
    std::string password;
    bool isAdmin;
    std::string purse;
    std::string phoneNumber;
    std::string address;
    int numOfBeds;
    std::string reserveDate;
    std::string checkoutDate;
    int userRoomNum;
};

#endif
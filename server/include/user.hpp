#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <vector>

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
        std::vector<const int&> numOfBeds,
        std::vector<std::string>& reserveDate,
        std::vector<std::string>& checkoutDate,
        std::vector<const int&> userRoomNum
    );
    User* User::checkInfo(std::string username, std::string password);
    int User::checkUser(std::string username);
    int User::getID();
    std::string User::viewUser();
    bool User::getAdmin();
    std::string User::viewUserForAdmin();
    int User::getPurse();
    void User::setPurse();
    void User::Reserve(int room_num, int num_of_beds, std::string reserve_date, std::string checkout_date);
    std::string User::showAllReservations();
    void User::updatePassword(std::string new_password);
    void User::updatePhoneNumber(std::string new_phone_number);
    void User::updateAddress(std::string new_address);
    bool User::hasCheckedOut(long long current_day, int room_num);
    int User::hasCheckedIn(long long current_date, int room_num);
    void User::Cancel(int room_num, int num_of_cancels)
    bool User::canCancel(int room_num, int num_of_cancels, long long current_days);
    void User::Leave(int room_num, int num_of_cancels, long long current_days);

private:
    int id;
    std::string username;
    std::string password;
    bool isAdmin;
    std::string purse;
    std::string phoneNumber;
    std::string address;
    std::vector<const int&> numOfBeds,
    std::vector<std::string>& reserveDate,
    std::vector<std::string>& checkoutDate,
    std::vector<const int&> userRoomNum
    long long User::calculateDays(int day, int month, int year);
    void User::removeRoom(int room_index);
    long long User::calculateDate(std:: string dates)
};

#endif
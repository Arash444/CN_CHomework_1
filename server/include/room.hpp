#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>
#include <vector>
#include <user.hpp>

class Room
{
public:
    Room(
        const int& number,
        const bool& status,
        const int& price,
        const int& maxCapacity,
        const int& capacityusers,
        std::vector<User*> roomUsers
    );
    std::string Room::viewRoom();
    std::string Room::viewRoomForAdmin();
    bool Room::isRoomAvailabe(int numOfBeds)
    int Room::getNumber();
    void Room::addUser(User* new_user);
    void User::passDay(long long current_day)
    void Room::modifyRoom(int new_price, int new_max_capacity);
    void Room::isRoomOccupied(int new_max_capacity);
    void Room::removeUser(int client_ID);
    int Room::reduceCapacity(int remove_capacity);

private:
    int number;
    bool status;
    int price;
    int maxCapacity;
    int capacityUsers;
    std::vector<User*> roomUsers;
};

#endif
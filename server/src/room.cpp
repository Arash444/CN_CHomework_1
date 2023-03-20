#include "room.hpp"

Room::Room(
        const int& number,
        const bool& status,
        const int& price,
        const int& maxCapacity,
        const int& capacityusers,
        std::vector<User*> room_users
    ): 
        number(number), 
        status(status), 
        price(price),
        maxCapacity(maxCapacity),
        capacityUsers(capacityUsers),
        roomUsers(roomUsers) {}
std::string Room::viewRoom()
{
    return "Room number: "+string(this->number) + "\nFull: "+string(this->status)+"\nPrice: "+string(this->price)+"\nMaxCapacity: "+string(this->maxCapacity) + "\nCapacity users: "+string(this->capacityUsers);
}

std::string Room::viewRoomForAdmin()
{
    std::string str = "Room number: "+string(this->number) + "\nFull: "+string(this->status)+"\nPrice: "+string(this->price)+"\nMaxCapacity: "+string(this->maxCapacity) + "\nCapacity users: "+string(this->capacityUsers)+"\nUsers: ";
    for(int j=0;j<this.roomUsers.size();j++)
    {
        str = str + this.roomUsers[j]->getUsername() + ",";
    }
    return str;
}
bool Room::isRoomAvailabe(int numOfBeds, long long current_days)
{
    int checkin_capacity = 0;
    for(int i = 0; i < this.roomUsers.size() ; i++)
        checkin_capacity += this.roomUsers[i]->hasCheckIn(current_days, this->number);
    if (checkin_capacity + numOfBeds > max_capacity)
        return true;
    else
        return false;
}
int Room::getNumber()
{
    return this.number;
}
int Room::getPrice()
{
    return this.price;
}
void Room::addUser(int numOfBeds, User* new_user)
{
    this->roomUsers = roomUsers.push_back(new_user);
}
void Room::passDay(long long current_day)
{
    for (int i = 0; i < roomUsers.size(); i++)
        if(roomUsers[i].hasCheckedOut(current_day, this->number))
            roomUsers.erase(roomUsers.begin() + i)
}
void Room::modifyRoom(int new_price, int new_max_capacity)
{   
    this->capacityUsers = new_max_capacity;
    this->price = new_price;
}
void Room::isRoomOccupied(int new_max_capacity)
{   
    if ((new_max_capacity < this->capacityUsers) && (roomUsers.size() != 0))
        return true;
    else 
        false;
}
void Room::removeUser(int client_ID)
{
    for(int i = o; i < roomUsers.size(); i++)
        if (client_ID == roomUsers[i].getID())
            roomUsers.erase(roomUsers.begin() + i)
}
void Room::removeCapacity(int remove_capacity)
{
    this->capacity -= remove_capacity;
}


#include "user.hpp"

User::User(
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
    ):
        id(id),
        username(username), 
        password(password),
        isAdmin(isAdmin),
        purse(purse),
        phoneNumber(phoneNumber),
        address(address),
        numOfBeds(numOfBeds), 
        reserveDate(reserveDate),
        checkoutDate(checkoutDate),
        userRoomNum(userRoomNum) {}

User* User::checkInfo(std::string username, std::string password)
{
    if (strcmp(username, this.username) == 0 && strcmp(password, this.password) == 0)
    {
        return this;
    }
    return NULL;
}

int User::checkUser(std::string username)
{
    if(strcmp(username, this->username) == 0)
    {
        return 1;
    }
    return 0;
}

std::string User::getUsername()
{
    return this.username;
}
int User::getID()
{
    return this.id;
}

std::string User::viewUser()
{
    return "ID: "+string(this.id)+"\nUsername: "+this.username+"\nPassword: "+this.password+"\nisAdmin: "+string(this.isAdmin)+"\nPurse: "+this.purse+"\nPhone number: "+this.phoneNumber+"\nAddress: "+this.address+"\nNum of beds: "+string(this.numOfBeds)+"\nReserve date: "+this.reserveDate+"\nCheckout date: "+this.checkoutDate+"\nUser room num: "+string(this.userRoomNum);
}
bool User::getAdmin()
{
    return this.isAdmin;
}
std::string User::viewUserForAdmin()
{
    return "ID: "+string(this.id)+"\nUsername: "+this.username+"\nisAdmin: "+string(this.isAdmin)+"\nPurse: "+this.purse+"\nPhone number: "+this.phoneNumber+"\nAddress: "+this.address+"\nNum of beds: "+string(this.numOfBeds)+"\nReserve date: "+this.reserveDate+"\nCheckout date: "+this.checkoutDate+"\nUser room num: "+string(this.userRoomNum);
}
int User::getPurse()
{
    return this.purse;
}
void User::setPurse(int price)
{
    this.purse = this.purse - price;
}
void User::Reserve(int room_num, int num_of_beds, std::string reserve_date, std::string checkout_date)
{
    this.userRoomNum = this.userRoomNum.push_back(room_num);
    this.numOfBeds = this.numOfBeds.push_back(numOfBeds);
    this.reserveDate = this.reserveDate.push_back(reserveDate);
    this.checkoutDate = this.checkoutDate.push_back(checkoutDate);
}
std::string User::showAllReservations()
{
    std::string message = null;
    for (int i = 0; i < this.userRoomNum.size(); i++)
        message += "Room Number: " + string(this.userRoomNum[i]) + "Number of Beds: " + string(this.num_of_beds[i]) +
        "Reservation Date: " + reserveDate + "Checkout Date: " + checkoutDate + "\n";
    return message;
}
void User::Cancel(int room_num, int num_of_cancels, long long current_days)
{
    for (int i = 0; i < userRoomNum.size(); i++)
    {
        long long checkin_days = calculateDate(reserveDate[i]);
        if(userRoomNum[i] == room_num && current_days < checkin_days)
        {
            if(num_of_cancels >= numOfBeds[i])
            {
                userRoomNum[i].removeUser(this->id);
                this->removeRoom(i);
                num_of_cancels -= numOfBeds[i];
            }
            else
            {
                numOfBeds[i] -= num_of_cancels;
                break;
            }
        }
    }
}
bool User::canCancel(int room_num, int num_of_cancels, long long current_days)
{
    int temp_num_of_beds = 0;
    for (int i = 0; i < userRoomNum.size(); i++)
    {
        long long checkin_days = calculateDate(reserveDate[i]);
        if(userRoomNum[i] == room_num && current_days < checkin_days)
            temp_num_of_beds += numOfBeds[i];
    }
    if (num_of_cancels > temp_num_of_beds || temp_num_of_beds == 0)
        return false;
    else 
        return true;
}
void User::Leave(int room_num, long long current_days)
{
    for (int i = 0; i < userRoomNum.size(); i++)
    {
        if(userRoomNum[i] == room_num && this->hasCheckedIn(current_days, room_num))
        {
            userRoomNum[i].remove_capacity(numOfBeds[i]);
            userRoomNum[i].removeUser(this->id);
            this->removeRoom(i);
        }
    }
}
void User::updatePassword(std::string new_password)
{
    this->password = new_password;
}
void User::updatePhoneNumber(std::string new_phone_number)
{
    this->phone_number = new_phone_number;
}
void User::updateAddress(std::string new_address)
{
    this->address = new_address;
}
int User::hasCheckedIn(long long current_date, int room_num)
{
    for(int i = 0; i < userRoomNum.size(); i++)
    {
        if (room_num == userRoomNum[i])
        {
            long long checkin_days, long long checkout_days;
            checkin_days = calculateDate(this->reserveDate[i]);
            checkout_days = calculateDate(this->checkoutDate[i]);
            if(current_date >= checkin_days && current_date < checkout_days)
                return numOfBeds[i];
            else
                return 0;
        }
    }
}
long long User::calculateDays(int day, int month, int year)
{
    long long current_day = year * 365 + day;
    if(month <= 6)
        current_day += (month - 1) * 31;
    else if(month < 12 && month > 6)
        current_day += 31 * 6 + (month - 7) * 30;
    else
        current_day += 31 * 6 + 30 * 5;
    return current_day;
}
bool User::hasCheckedOut(long long current_day, int room_num)
{
    for (int i = 0; i < userRoomNum.size(); i++)
    {
        if(userRoomNum[i] == room_num)
        {
            long long checkout_days = calculateDate(this->checkoutDate[i]);
            if(current_date >= checkout_days)
            {
                this->removeRoom(i);
                i--;
                return true;
            }
            else
                return false;
        }
    }
}
void User::removeRoom(int room_index)
{
    numOfBeds.erase(numOfBeds.begin() + room_index);
    checkoutDate.erase(checkoutDate.begin() + room_index);
    reserveDate.erase(reserveDate.begin() + room_index);
    userRoomNum.erase(userRoomNum.begin() + room_index);
}
long long User::calculateDate(std:: string dates)
{
    int day = std::stoi(dates.substr(0, 2));
    int month = std::stoi(dates.substr(3, 2));
    int year = std::stoi(dates.substr(6, 4));
    return calculateDays(day, month, year);
}
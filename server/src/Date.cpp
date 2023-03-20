#include "../include/Date.hpp"

bool Date::setDate(const std::string &dateStr)
{
    if (!isValidDateFormat(dateStr))
        return false;

    int day = std::stoi(dateStr.substr(0, 2));
    int month = std::stoi(dateStr.substr(3, 2));
    int year = std::stoi(dateStr.substr(6, 4));
    this->current_day = calculateDays(day, month, year)
    return true;
}
long long Date::calculateDays(int day, int month, int year)
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
bool Date::isValidDateFormat(const std::string &dateStr)
{
    // Regular expression to match a date in the format DD-MM-YYYY
    std::regex dateRegex("\\d{2}-\\d{2}-\\d{4}");
    if(!std::regex_match(dateStr, dateRegex))
        return false;
    
    // Check if the range of the date is valid
    int day = std::stoi(dateStr.substr(0, 2));
    int month = std::stoi(dateStr.substr(3, 2));
    int year = std::stoi(dateStr.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
        return false;

    return true;
}
void Date::passDay(int num_days)
{
    this->current_day = this->current_day + num_days;
}
long long getCurrentDay()
{
    return this->current_day;
}
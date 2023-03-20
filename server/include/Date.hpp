#ifndef _DATE_H_
#define _DATE_H_

#include <regex>
#include <string>


class Date
{
public:
    bool setDate(const std::string& dateStr);
    void Date::passDay(int num_days);
    long long getCurrentDay();

private:
    //int year;
    //int month;
    //int day;
    long long current_day;

    bool isValidDateFormat(const std::string& dateStr);
    long long calculateDays(int day, int month, int year);
    //void updateDate();
};

#endif
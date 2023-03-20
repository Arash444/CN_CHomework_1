#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class Exception
{
public:
    std::string show();

private:
    const std::string msg;
};

#endif
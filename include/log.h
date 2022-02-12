#ifndef __LOG_H_
#define __LOG_H_

#include <iostream>
#include <ctime>
#include <cstring>

class Log{
    public:
    Log() = default;
    ~Log() = default;
    void i(const char *msg);
    void w(const char *msg);
    void e(const char *msg);
};


#endif
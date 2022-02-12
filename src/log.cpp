#include "log.h"

const char *getTime() {
    time_t now = time(0);
    char * result = ctime(&now);
    result[strlen(result) - 1] = '\0';
    return result;
}

void Log::i(const char *msg) {
    std::cout << getTime() << "   I   " << msg << std::endl;
}
void Log::w(const char *msg) {
    std::cout << "\033[33m" << getTime() << "   W   " << msg << "\033[0m" << std::endl;
}
void Log::e(const char *msg){
    std::cout  << "\033[31m" << getTime() << "   E   " << msg << "\033[0m" << std::endl;
}
#include "log.h"

static const char *getTime() {
    time_t now = time(0);
    char * result = ctime(&now);
    result[strlen(result) - 1] = '\0';
    return result;
}

Log::Log() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void Log::i(const char *msg) {
    std::cout << getTime() << "   I   " << msg << std::endl;
}
void Log::w(const char *msg) {
    std::cout << "\033[33m" << getTime() << "   W   " << msg << "\033[0m\n";
}
void Log::e(const char *msg){
    std::cout  << "\033[31m" << getTime() << "   E   " << msg << "\033[0m\n";
}

#include "../include/utils.hpp"

#include <sstream>
#include <random>
#include <ctime>
#include <iomanip>

namespace hacksim {

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

static std::mt19937& getRandomEngine() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

int randomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(getRandomEngine());
}

std::string randomIP() {
    std::stringstream ss;
    ss << randomInt(1, 254) << "." << randomInt(0, 255) << "." 
       << randomInt(0, 255) << "." << randomInt(1, 254);
    return ss.str();
}

std::string randomMAC() {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 6; i++) {
        if (i > 0) ss << ":";
        ss << std::setw(2) << randomInt(0, 255);
    }
    return ss.str();
}

std::string currentTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

} // namespace hacksim

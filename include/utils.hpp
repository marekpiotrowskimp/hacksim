#pragma once

#include <string>
#include <vector>

namespace hacksim {

std::vector<std::string> split(const std::string& str, char delimiter = ' ');
std::string trim(const std::string& str);
std::string randomIP();
std::string randomMAC();
int randomInt(int min, int max);
std::string currentTimestamp();

} // namespace hacksim

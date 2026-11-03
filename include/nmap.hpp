#pragma once

#include <string>
#include <vector>
#include <functional>

namespace hacksim {

struct CommandResult;

// Nmap simulation with animated output
CommandResult cmd_nmap(const std::vector<std::string>& args, 
                       std::function<void(const std::string&)> on_line);

// Simple non-animated version
CommandResult cmd_nmap_simple(const std::vector<std::string>& args);

} // namespace hacksim

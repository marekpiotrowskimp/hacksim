#pragma once

#include <string>
#include <vector>

namespace hacksim {

struct CommandResult;

CommandResult cmd_help(const std::vector<std::string>& args);
CommandResult cmd_clear(const std::vector<std::string>& args);
CommandResult cmd_exit(const std::vector<std::string>& args);
CommandResult cmd_whoami(const std::vector<std::string>& args);
CommandResult cmd_id(const std::vector<std::string>& args);
CommandResult cmd_uname(const std::vector<std::string>& args);
CommandResult cmd_hostname(const std::vector<std::string>& args);
CommandResult cmd_pwd(const std::vector<std::string>& args);
CommandResult cmd_ps(const std::vector<std::string>& args);
CommandResult cmd_netstat(const std::vector<std::string>& args);
CommandResult cmd_ifconfig(const std::vector<std::string>& args);
CommandResult cmd_date(const std::vector<std::string>& args);
CommandResult cmd_uptime(const std::vector<std::string>& args);

} // namespace hacksim

#pragma once

#include <string>
#include <vector>

namespace hacksim {

struct CommandResult;

// Nmap simulation
CommandResult cmd_nmap_simple(const std::vector<std::string>& args);

// WiFi hacking tools (aircrack-ng suite)
CommandResult cmd_airmon(const std::vector<std::string>& args);
CommandResult cmd_airodump(const std::vector<std::string>& args);
CommandResult cmd_aireplay(const std::vector<std::string>& args);
CommandResult cmd_aircrack(const std::vector<std::string>& args);

// Packet sniffing
CommandResult cmd_tcpdump(const std::vector<std::string>& args);
CommandResult cmd_tshark(const std::vector<std::string>& args);

// MITM / ARP
CommandResult cmd_ettercap(const std::vector<std::string>& args);
CommandResult cmd_arpspoof(const std::vector<std::string>& args);

// Exploitation
CommandResult cmd_msfconsole(const std::vector<std::string>& args);
CommandResult cmd_searchsploit(const std::vector<std::string>& args);

// Password cracking
CommandResult cmd_hydra(const std::vector<std::string>& args);
CommandResult cmd_john(const std::vector<std::string>& args);
CommandResult cmd_hashcat(const std::vector<std::string>& args);

// Web scanning
CommandResult cmd_nikto(const std::vector<std::string>& args);
CommandResult cmd_sqlmap(const std::vector<std::string>& args);
CommandResult cmd_dirb(const std::vector<std::string>& args);
CommandResult cmd_gobuster(const std::vector<std::string>& args);

// Other recon
CommandResult cmd_whois(const std::vector<std::string>& args);
CommandResult cmd_dig(const std::vector<std::string>& args);
CommandResult cmd_traceroute(const std::vector<std::string>& args);
CommandResult cmd_curl(const std::vector<std::string>& args);
CommandResult cmd_wget(const std::vector<std::string>& args);

// SSH/connections
CommandResult cmd_ssh(const std::vector<std::string>& args);
CommandResult cmd_nc(const std::vector<std::string>& args);

} // namespace hacksim

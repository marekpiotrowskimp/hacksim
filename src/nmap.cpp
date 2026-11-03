#include "../include/nmap.hpp"
#include "../include/terminal.hpp"
#include "../include/utils.hpp"

#include <sstream>
#include <iomanip>

namespace hacksim {

struct PortInfo {
    int port;
    std::string state;
    std::string service;
    std::string version;
};

CommandResult cmd_nmap_simple(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine("Nmap 7.94 ( https://nmap.org )"),
            line({seg("ERROR: No target specified.", TermColor::Red)}),
            plainLine(""),
            plainLine("Usage: nmap [options] <target>"),
            plainLine(""),
            plainLine("Examples:"),
            plainLine("  nmap 192.168.1.1"),
            plainLine("  nmap scanme.nmap.org"),
            plainLine("  nmap 10.0.0.0/24")
        };
        result.success = false;
        return result;
    }
    
    std::string target = args[0];
    bool verbose = false;
    bool service_scan = false;
    
    for (const auto& arg : args) {
        if (arg == "-v" || arg == "-vv") verbose = true;
        if (arg == "-sV") service_scan = true;
    }
    
    // Generate random but realistic results
    std::vector<PortInfo> ports = {
        {22, "open", "ssh", "OpenSSH 8.9p1 Ubuntu"},
        {80, "open", "http", "Apache httpd 2.4.54"},
        {443, "open", "https", "Apache httpd 2.4.54"},
        {3306, "filtered", "mysql", ""},
        {5432, "open", "postgresql", "PostgreSQL 15.2"},
        {8080, "open", "http-proxy", "Squid http proxy 5.7"},
        {21, "closed", "ftp", ""},
        {23, "closed", "telnet", ""},
        {25, "filtered", "smtp", ""},
        {445, "filtered", "microsoft-ds", ""},
    };
    
    // Randomly select some ports
    int num_ports = randomInt(3, 7);
    
    result.output.push_back(plainLine(""));
    result.output.push_back(plainLine("Starting Nmap 7.94 ( https://nmap.org ) at " + currentTimestamp()));
    
    if (verbose) {
        result.output.push_back(plainLine("Initiating Ping Scan at " + currentTimestamp().substr(11, 8)));
        result.output.push_back(plainLine("Scanning " + target + " [4 ports]"));
        result.output.push_back(plainLine("Completed Ping Scan at " + currentTimestamp().substr(11, 8) + ", 0.02s elapsed (1 total hosts)"));
        result.output.push_back(plainLine("Initiating Parallel DNS resolution of 1 host. at " + currentTimestamp().substr(11, 8)));
        result.output.push_back(plainLine("Completed Parallel DNS resolution of 1 host. at " + currentTimestamp().substr(11, 8) + ", 0.01s elapsed"));
        result.output.push_back(plainLine("Initiating SYN Stealth Scan at " + currentTimestamp().substr(11, 8)));
    }
    
    result.output.push_back(plainLine("Nmap scan report for " + target));
    result.output.push_back(plainLine("Host is up (0.00" + std::to_string(randomInt(10, 99)) + "s latency)."));
    result.output.push_back(plainLine(""));
    
    if (service_scan) {
        result.output.push_back(plainLine("PORT      STATE    SERVICE         VERSION"));
    } else {
        result.output.push_back(plainLine("PORT      STATE    SERVICE"));
    }
    
    for (int i = 0; i < num_ports && i < static_cast<int>(ports.size()); i++) {
        const auto& p = ports[i];
        std::stringstream ss;
        ss << std::left << std::setw(9) << (std::to_string(p.port) + "/tcp") << " ";
        
        TermColor state_color = TermColor::Default;
        if (p.state == "open") {
            state_color = TermColor::Green;
        } else if (p.state == "filtered") {
            state_color = TermColor::Yellow;
        } else {
            state_color = TermColor::Red;
        }
        
        std::stringstream service_ss;
        service_ss << std::left << std::setw(15) << p.service;
        
        if (service_scan && !p.version.empty()) {
            result.output.push_back(line({
                seg(ss.str()),
                seg(p.state, state_color),
                seg("   " + service_ss.str() + " " + p.version)
            }));
        } else {
            result.output.push_back(line({
                seg(ss.str()),
                seg(p.state, state_color),
                seg("   " + service_ss.str())
            }));
        }
    }
    
    result.output.push_back(plainLine(""));
    
    if (service_scan) {
        result.output.push_back(plainLine("Service detection performed. Please report any incorrect results at https://nmap.org/submit/"));
    }
    
    double scan_time = randomInt(100, 500) / 100.0;
    result.output.push_back(plainLine("Nmap done: 1 IP address (1 host up) scanned in " + 
                           std::to_string(scan_time).substr(0, 4) + " seconds"));
    result.output.push_back(plainLine(""));
    
    return result;
}

} // namespace hacksim

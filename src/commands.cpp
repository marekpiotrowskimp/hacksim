#include "../include/commands.hpp"
#include "../include/terminal.hpp"
#include "../include/utils.hpp"

#include <sstream>
#include <iomanip>
#include <ctime>

namespace hacksim {

CommandResult cmd_help(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {
        plainLine(""),
        line({seg("=== HACKSIM - Kali Linux Terminal Simulator ===", TermColor::Green, true)}),
        plainLine(""),
        line({seg("Basic:", TermColor::Yellow, true)}),
        plainLine("  help              Show this help message"),
        plainLine("  clear             Clear the terminal screen"),
        plainLine("  exit, quit        Exit the terminal"),
        plainLine(""),
        line({seg("System Info:", TermColor::Yellow, true)}),
        plainLine("  whoami            Display current user"),
        plainLine("  id                Display user and group IDs"),
        plainLine("  uname [-a]        System information"),
        plainLine("  hostname          Display hostname"),
        plainLine("  uptime            System uptime"),
        plainLine("  date              Current date/time"),
        plainLine("  htop, top         Interactive process monitor"),
        plainLine(""),
        line({seg("File System:", TermColor::Yellow, true)}),
        plainLine("  pwd               Print working directory"),
        plainLine("  ls [-la]          List directory contents"),
        plainLine("  cd <dir>          Change directory"),
        plainLine("  cat <file>        Display file contents"),
        plainLine(""),
        line({seg("Network Scanning:", TermColor::Yellow, true)}),
        plainLine("  nmap <target>     Port scanning"),
        plainLine("  whois <domain>    Domain registration info"),
        plainLine("  dig <domain>      DNS lookup"),
        plainLine("  traceroute <host> Trace packet route"),
        plainLine("  ifconfig          Network interfaces"),
        plainLine("  netstat           Network connections"),
        plainLine(""),
        line({seg("WiFi Hacking (aircrack-ng):", TermColor::Red, true)}),
        plainLine("  airmon-ng         Monitor mode control"),
        plainLine("  airodump-ng       WiFi network scanner"),
        plainLine("  aireplay-ng       Deauth/injection attacks"),
        plainLine("  aircrack-ng       WPA/WEP cracker"),
        plainLine(""),
        line({seg("Packet Sniffing:", TermColor::Yellow, true)}),
        plainLine("  tcpdump           Capture network packets"),
        plainLine("  tshark            Wireshark CLI"),
        plainLine(""),
        line({seg("MITM Attacks:", TermColor::Red, true)}),
        plainLine("  ettercap          MITM attack framework"),
        plainLine("  arpspoof          ARP spoofing"),
        plainLine(""),
        line({seg("Exploitation:", TermColor::Red, true)}),
        plainLine("  msfconsole        Metasploit Framework"),
        plainLine("  searchsploit      Exploit database search"),
        plainLine(""),
        line({seg("Password Cracking:", TermColor::Yellow, true)}),
        plainLine("  hydra             Network login cracker"),
        plainLine("  john              Password hash cracker"),
        plainLine("  hashcat           GPU hash cracker"),
        plainLine(""),
        line({seg("Web Scanning:", TermColor::Yellow, true)}),
        plainLine("  nikto             Web server scanner"),
        plainLine("  sqlmap            SQL injection tool"),
        plainLine("  dirb              Directory brute-forcer"),
        plainLine("  gobuster          Directory/DNS scanner"),
        plainLine(""),
        line({seg("Utilities:", TermColor::Yellow, true)}),
        plainLine("  curl <url>        HTTP client"),
        plainLine("  wget <url>        Download files"),
        plainLine("  ssh <host>        SSH connection"),
        plainLine("  nc <host> <port>  Netcat"),
        plainLine("  ps [aux]          Process list"),
        plainLine("")
    };
    return result;
}

CommandResult cmd_clear(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.clear_screen = true;
    return result;
}

CommandResult cmd_exit(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.should_exit = true;
    result.output = {line({seg("Goodbye.", TermColor::GrayDark)})};
    return result;
}

CommandResult cmd_whoami(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {plainLine("root")};
    return result;
}

CommandResult cmd_id(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {plainLine("uid=0(root) gid=0(root) groups=0(root),1(bin),2(daemon),3(sys),4(adm)")};
    return result;
}

CommandResult cmd_uname(const std::vector<std::string>& args) {
    CommandResult result;
    bool show_all = false;
    for (const auto& arg : args) {
        if (arg == "-a" || arg == "--all") {
            show_all = true;
        }
    }
    
    if (show_all) {
        result.output = {plainLine("Linux kali 6.1.0-kali9-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.1.27-1kali1 x86_64 GNU/Linux")};
    } else {
        result.output = {plainLine("Linux")};
    }
    return result;
}

CommandResult cmd_hostname(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {plainLine("kali")};
    return result;
}

CommandResult cmd_pwd(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {plainLine("/root")};
    return result;
}

CommandResult cmd_ps(const std::vector<std::string>& args) {
    CommandResult result;
    bool show_all = false;
    for (const auto& arg : args) {
        if (arg == "aux" || arg == "-aux" || arg == "-ef") {
            show_all = true;
        }
    }
    
    if (show_all) {
        result.output = {
            plainLine("USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND"),
            plainLine("root         1  0.0  0.1 169436 13120 ?        Ss   00:01   0:02 /sbin/init"),
            plainLine("root         2  0.0  0.0      0     0 ?        S    00:01   0:00 [kthreadd]"),
            plainLine("root       412  0.0  0.2 238764 20480 ?        Ss   00:01   0:00 /usr/sbin/sshd -D"),
            plainLine("root       486  0.1  0.3 347812 28416 ?        Ssl  00:01   0:05 /usr/sbin/NetworkManager"),
            plainLine("root       521  0.0  0.1 165788 12288 ?        Ss   00:01   0:00 /usr/sbin/apache2 -k start"),
            plainLine("www-data   534  0.0  0.1 167324  8192 ?        S    00:01   0:00 /usr/sbin/apache2 -k start"),
            plainLine("root       612  0.2  0.5 512648 45056 ?        Ssl  00:01   0:08 /usr/bin/python3 /usr/share/exploitdb/searchsploit"),
            plainLine("postgres   701  0.0  0.4 215384 32768 ?        Ss   00:01   0:01 /usr/lib/postgresql/15/bin/postgres"),
            plainLine("root       842  0.0  0.2 178932 16384 tty1     Ss+  00:01   0:00 /bin/login -f"),
            plainLine("root       901  0.5  0.8 892416 65536 pts/0    Ssl+ 00:02   0:15 /usr/bin/msfconsole"),
            plainLine("root       " + std::to_string(randomInt(1000, 9999)) + "  0.0  0.1  12784  3584 pts/1    R+   " + currentTimestamp().substr(11, 5) + "   0:00 ps aux")
        };
    } else {
        result.output = {
            plainLine("  PID TTY          TIME CMD"),
            plainLine("  901 pts/0    00:00:15 msfconsole"),
            plainLine("  " + std::to_string(randomInt(1000, 9999)) + " pts/1    00:00:00 ps")
        };
    }
    return result;
}

CommandResult cmd_netstat(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {
        plainLine("Active Internet connections (servers and established)"),
        plainLine("Proto Recv-Q Send-Q Local Address           Foreign Address         State"),
        plainLine("tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN"),
        plainLine("tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN"),
        plainLine("tcp        0      0 0.0.0.0:443             0.0.0.0:*               LISTEN"),
        plainLine("tcp        0      0 127.0.0.1:5432          0.0.0.0:*               LISTEN"),
        plainLine("tcp        0      0 192.168.1.105:22        192.168.1.1:54832       ESTABLISHED"),
        plainLine("tcp        0      0 192.168.1.105:443       " + randomIP() + ":443       TIME_WAIT"),
        plainLine("tcp6       0      0 :::22                   :::*                    LISTEN"),
        plainLine("udp        0      0 0.0.0.0:68              0.0.0.0:*               "),
        plainLine("udp        0      0 192.168.1.105:123       0.0.0.0:*               ")
    };
    return result;
}

CommandResult cmd_ifconfig(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {
        line({seg("eth0", TermColor::Green), seg(": flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500")}),
        plainLine("        inet 192.168.1.105  netmask 255.255.255.0  broadcast 192.168.1.255"),
        plainLine("        inet6 fe80::a00:27ff:fe8e:8aa8  prefixlen 64  scopeid 0x20<link>"),
        plainLine("        ether 08:00:27:8e:8a:a8  txqueuelen 1000  (Ethernet)"),
        plainLine("        RX packets 284712  bytes 341923847 (326.0 MiB)"),
        plainLine("        RX errors 0  dropped 0  overruns 0  frame 0"),
        plainLine("        TX packets 118432  bytes 12847321 (12.2 MiB)"),
        plainLine("        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0"),
        plainLine(""),
        line({seg("lo", TermColor::Green), seg(": flags=73<UP,LOOPBACK,RUNNING>  mtu 65536")}),
        plainLine("        inet 127.0.0.1  netmask 255.0.0.0"),
        plainLine("        inet6 ::1  prefixlen 128  scopeid 0x10<host>"),
        plainLine("        loop  txqueuelen 1000  (Local Loopback)"),
        plainLine("        RX packets 1284  bytes 104832 (102.3 KiB)"),
        plainLine("        RX errors 0  dropped 0  overruns 0  frame 0"),
        plainLine("        TX packets 1284  bytes 104832 (102.3 KiB)"),
        plainLine("        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0"),
        plainLine(""),
        line({seg("wlan0", TermColor::Green), seg(": flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500")}),
        plainLine("        ether " + randomMAC() + "  txqueuelen 1000  (Ethernet)"),
        plainLine("        RX packets 0  bytes 0 (0.0 B)"),
        plainLine("        TX packets 0  bytes 0 (0.0 B)")
    };
    return result;
}

CommandResult cmd_date(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    result.output = {plainLine(currentTimestamp())};
    return result;
}

CommandResult cmd_uptime(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    int hours = randomInt(1, 72);
    int mins = randomInt(0, 59);
    int users = randomInt(1, 3);
    std::stringstream ss;
    ss << " " << currentTimestamp().substr(11, 8) << " up " << hours << ":" << std::setfill('0') << std::setw(2) << mins;
    ss << ", " << users << " user" << (users > 1 ? "s" : "") << ", load average: ";
    ss << std::fixed << std::setprecision(2) << (randomInt(10, 250) / 100.0) << ", ";
    ss << std::fixed << std::setprecision(2) << (randomInt(10, 200) / 100.0) << ", ";
    ss << std::fixed << std::setprecision(2) << (randomInt(10, 150) / 100.0);
    result.output = {plainLine(ss.str())};
    return result;
}

} // namespace hacksim

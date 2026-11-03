#include "../include/tools.hpp"
#include "../include/terminal.hpp"
#include "../include/utils.hpp"

#include <sstream>
#include <iomanip>

namespace hacksim {

// ============== AIRCRACK-NG SUITE ==============

CommandResult cmd_airmon(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Airmon-ng 1.7", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: airmon-ng <start|stop|check> <interface> [channel]"),
            plainLine(""),
            plainLine("       airmon-ng check kill    - Kill interfering processes"),
            plainLine("       airmon-ng start wlan0   - Start monitor mode"),
            plainLine("       airmon-ng stop wlan0mon - Stop monitor mode"),
        };
        return result;
    }
    
    std::string action = args[0];
    std::string iface = args.size() > 1 ? args[1] : "wlan0";
    
    if (action == "check" && args.size() > 1 && args[1] == "kill") {
        result.output = {
            plainLine(""),
            plainLine("Killing these processes:"),
            plainLine(""),
            plainLine("  PID Name"),
            plainLine("  486 NetworkManager"),
            plainLine("  521 wpa_supplicant"),
            plainLine("  612 dhclient"),
            plainLine(""),
            line({seg("All interfering processes killed.", TermColor::Green)}),
        };
    } else if (action == "start") {
        result.output = {
            plainLine(""),
            plainLine("PHY\tInterface\tDriver\t\tChipset"),
            plainLine(""),
            line({seg("phy0\t" + iface + "\t\tath9k_htc\tQualcomm Atheros AR9271", TermColor::White)}),
            plainLine(""),
            plainLine("\t\t(mac80211 monitor mode vif enabled for [phy0]" + iface + " on [phy0]" + iface + "mon)"),
            plainLine("\t\t(mac80211 station mode vif disabled for [phy0]" + iface + ")"),
            plainLine(""),
            line({seg("Monitor mode enabled on " + iface + "mon", TermColor::Green)}),
        };
    } else if (action == "stop") {
        result.output = {
            plainLine(""),
            plainLine("PHY\tInterface\tDriver\t\tChipset"),
            plainLine(""),
            line({seg("phy0\t" + iface + "\t\tath9k_htc\tQualcomm Atheros AR9271", TermColor::White)}),
            plainLine(""),
            line({seg("Monitor mode disabled.", TermColor::Yellow)}),
        };
    }
    
    return result;
}

CommandResult cmd_airodump(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Airodump-ng 1.7", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: airodump-ng <options> <interface>"),
            plainLine(""),
            plainLine("Options:"),
            plainLine("  -c <channel>    : Capture on specific channel"),
            plainLine("  -w <prefix>     : Write capture to file"),
            plainLine("  --bssid <bssid> : Filter by BSSID"),
            plainLine("  --essid <essid> : Filter by ESSID"),
        };
        return result;
    }
    
    // Generate fake WiFi networks
    result.output = {
        plainLine(""),
        line({seg(" CH 6 ][ Elapsed: 24 s ][ " + currentTimestamp(), TermColor::White)}),
        plainLine(""),
        line({seg(" BSSID              PWR  Beacons    #Data  #/s  CH  MB   ENC  CIPHER AUTH ESSID", TermColor::Cyan)}),
        plainLine(""),
        line({seg(" " + randomMAC() + "  -42      156       89    2   6  54e  WPA2 CCMP   PSK  ", TermColor::White), seg("TP-Link_5G_Home", TermColor::Green)}),
        line({seg(" " + randomMAC() + "  -58       98       34    1   6  54e  WPA2 CCMP   PSK  ", TermColor::White), seg("NETGEAR-Guest", TermColor::Yellow)}),
        line({seg(" " + randomMAC() + "  -67       45       12    0   1  54e  WPA2 CCMP   PSK  ", TermColor::White), seg("Linksys_2.4GHz", TermColor::White)}),
        line({seg(" " + randomMAC() + "  -71       23        5    0  11  54e  WEP  WEP        ", TermColor::White), seg("OldRouter", TermColor::Red)}),
        line({seg(" " + randomMAC() + "  -78       12        2    0   6  54e  OPN              ", TermColor::White), seg("FreeWiFi", TermColor::Red)}),
        plainLine(""),
        line({seg(" BSSID              STATION            PWR   Rate    Lost  Frames  Probe", TermColor::Cyan)}),
        plainLine(""),
        line({seg(" " + randomMAC() + "  " + randomMAC() + "  -34   54e-54e     0      89  ", TermColor::White)}),
        line({seg(" " + randomMAC() + "  " + randomMAC() + "  -56   11e- 1e     2      23  ", TermColor::White)}),
        plainLine(""),
        line({seg("Press Ctrl+C to stop capture...", TermColor::GrayDark)}),
    };
    
    return result;
}

CommandResult cmd_aireplay(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Aireplay-ng 1.7", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: aireplay-ng <options> <interface>"),
            plainLine(""),
            plainLine("Attack modes:"),
            plainLine("  -0 <count>   : Deauthentication attack"),
            plainLine("  -1 <delay>   : Fake authentication"),
            plainLine("  -3           : ARP request replay attack"),
            plainLine("  -9           : Injection test"),
        };
        return result;
    }
    
    // Deauth attack simulation
    if (args[0] == "-0" || args[0] == "--deauth") {
        result.output = {
            plainLine(""),
            line({seg("Sending DeAuth to broadcast -- BSSID: [" + randomMAC() + "]", TermColor::Yellow)}),
            plainLine(currentTimestamp().substr(11) + "  Sending 64 directed DeAuth. STMAC: [" + randomMAC() + "] [ 0|62 ACKs]"),
            plainLine(currentTimestamp().substr(11) + "  Sending 64 directed DeAuth. STMAC: [" + randomMAC() + "] [ 5|58 ACKs]"),
            plainLine(currentTimestamp().substr(11) + "  Sending 64 directed DeAuth. STMAC: [" + randomMAC() + "] [12|52 ACKs]"),
            plainLine(currentTimestamp().substr(11) + "  Sending 64 directed DeAuth. STMAC: [" + randomMAC() + "] [23|41 ACKs]"),
            plainLine(""),
            line({seg("Deauthentication packets sent successfully.", TermColor::Green)}),
        };
    }
    
    return result;
}

CommandResult cmd_aircrack(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Aircrack-ng 1.7", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: aircrack-ng [options] <capture file(s)>"),
            plainLine(""),
            plainLine("Options:"),
            plainLine("  -w <wordlist> : Path to wordlist file"),
            plainLine("  -b <bssid>    : Target BSSID"),
            plainLine("  -e <essid>    : Target ESSID"),
            plainLine("  -a <mode>     : Force attack mode (1=WEP, 2=WPA-PSK)"),
        };
        return result;
    }
    
    result.output = {
        plainLine(""),
        line({seg("                              Aircrack-ng 1.7", TermColor::Cyan, true)}),
        plainLine(""),
        plainLine("      [00:00:32] " + std::to_string(randomInt(10000, 99999)) + "/" + std::to_string(randomInt(100000, 999999)) + " keys tested (" + std::to_string(randomInt(800, 1200)) + ".42 k/s)"),
        plainLine(""),
        plainLine("      Time left: 2 minutes, 34 seconds                     " + std::to_string(randomInt(1, 99)) + "." + std::to_string(randomInt(10, 99)) + "%"),
        plainLine(""),
        line({seg("                    KEY FOUND! [ ", TermColor::Green), seg("s3cur3p4ss!", TermColor::Yellow, true), seg(" ]", TermColor::Green)}),
        plainLine(""),
        plainLine("      Master Key     : A1 B2 C3 D4 E5 F6 G7 H8 I9 J0 K1 L2 M3 N4 O5 P6"),
        plainLine(""),
        plainLine("      Transient Key  : Q7 R8 S9 T0 U1 V2 W3 X4 Y5 Z6 A7 B8 C9 D0 E1 F2"),
        plainLine("                       G3 H4 I5 J6 K7 L8 M9 N0 O1 P2 Q3 R4 S5 T6 U7 V8"),
        plainLine(""),
        plainLine("      EAPOL HMAC     : W9 X0 Y1 Z2 A3 B4 C5 D6 E7 F8 G9 H0 I1 J2 K3 L4"),
    };
    
    return result;
}

// ============== PACKET SNIFFING ==============

CommandResult cmd_tcpdump(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("tcpdump version 4.99.1", TermColor::White)}),
            plainLine("libpcap version 1.10.1"),
            plainLine(""),
            plainLine("Usage: tcpdump [-i interface] [-w file] [-c count] [expression]"),
        };
        return result;
    }
    
    result.output = {
        plainLine("tcpdump: verbose output suppressed, use -v or -vv for full protocol decode"),
        plainLine("listening on eth0, link-type EN10MB (Ethernet), capture size 262144 bytes"),
    };
    
    // Generate some fake packets
    for (int i = 0; i < 8; i++) {
        std::stringstream ss;
        ss << currentTimestamp().substr(11) << "." << std::setfill('0') << std::setw(6) << randomInt(0, 999999);
        ss << " IP " << randomIP() << "." << randomInt(1024, 65535);
        ss << " > " << randomIP() << "." << randomInt(1, 1024);
        ss << ": Flags [";
        
        std::vector<std::string> flags = {"S", ".", "P.", "F.", "S."};
        ss << flags[randomInt(0, flags.size()-1)];
        ss << "], seq " << randomInt(1000000, 9999999) << ", ack " << randomInt(1, 9999);
        ss << ", win " << randomInt(100, 65535) << ", length " << randomInt(0, 1500);
        
        result.output.push_back(plainLine(ss.str()));
    }
    
    result.output.push_back(plainLine(""));
    result.output.push_back(plainLine("8 packets captured"));
    result.output.push_back(plainLine("8 packets received by filter"));
    result.output.push_back(plainLine("0 packets dropped by kernel"));
    
    return result;
}

CommandResult cmd_tshark(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("TShark (Wireshark) 4.0.6", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: tshark [options] ..."),
            plainLine(""),
            plainLine("Capture options:"),
            plainLine("  -i <interface>   : name or idx of interface"),
            plainLine("  -f <filter>      : packet filter in libpcap syntax"),
            plainLine("  -c <count>       : stop after n packets"),
            plainLine("  -w <outfile>     : write packets to file"),
        };
        return result;
    }
    
    result.output = {
        plainLine("Capturing on 'eth0'"),
    };
    
    for (int i = 1; i <= 5; i++) {
        std::stringstream ss;
        ss << std::setw(4) << i << " " << std::fixed << std::setprecision(6) << (randomInt(1, 99) / 10.0);
        ss << " " << std::setw(15) << randomIP() << " -> " << std::setw(15) << randomIP();
        
        std::vector<std::string> protos = {"TCP", "UDP", "HTTP", "TLS", "DNS", "ICMP"};
        std::string proto = protos[randomInt(0, protos.size()-1)];
        ss << " " << proto << " " << randomInt(40, 1500) << " ";
        
        if (proto == "HTTP") ss << "GET /index.html HTTP/1.1";
        else if (proto == "DNS") ss << "Standard query A www.example.com";
        else if (proto == "TCP") ss << randomInt(1024, 65535) << " -> " << randomInt(1, 1024) << " [SYN]";
        else if (proto == "TLS") ss << "Client Hello";
        else ss << "Packet data";
        
        result.output.push_back(plainLine(ss.str()));
    }
    
    result.output.push_back(plainLine("5 packets captured"));
    
    return result;
}

// ============== MITM / ARP ==============

CommandResult cmd_ettercap(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("ettercap 0.8.3.1", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: ettercap [OPTIONS] [TARGET1] [TARGET2]"),
            plainLine(""),
            plainLine("Sniffing and Attack options:"),
            plainLine("  -T        : text only interface"),
            plainLine("  -q        : quiet mode"),
            plainLine("  -M arp    : ARP poisoning MITM attack"),
            plainLine("  -i iface  : network interface"),
            plainLine(""),
            plainLine("TARGET is in the format MAC/IP/PORT"),
        };
        return result;
    }
    
    result.output = {
        plainLine(""),
        line({seg("ettercap 0.8.3.1 copyright 2001-2020", TermColor::Cyan)}),
        plainLine(""),
        plainLine("Listening on:"),
        plainLine("  eth0 -> 08:00:27:8E:8A:A8"),
        plainLine("        192.168.1.105/255.255.255.0"),
        plainLine(""),
        line({seg("ARP poisoning victims:", TermColor::Yellow)}),
        plainLine(""),
        plainLine(" GROUP 1 : 192.168.1.1 " + randomMAC()),
        plainLine(" GROUP 2 : 192.168.1.100 " + randomMAC()),
        plainLine(""),
        line({seg("Starting Unified sniffing...", TermColor::Green)}),
        plainLine(""),
        plainLine("Text only Interface activated..."),
        plainLine("Hit 'h' for inline help"),
        plainLine(""),
        plainLine("ARP poisoning started..."),
        plainLine("Sniffing packets..."),
    };
    
    return result;
}

CommandResult cmd_arpspoof(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            plainLine("Usage: arpspoof [-i interface] [-t target] host"),
            plainLine(""),
            plainLine("  -i interface : Specify interface"),
            plainLine("  -t target    : Specify target IP"),
            plainLine("  host         : Host to intercept packets for"),
        };
        return result;
    }
    
    std::string target = args.size() > 1 ? args[1] : "192.168.1.1";
    
    result.output = {
        line({seg("arpspoof: ", TermColor::Yellow), seg("sending spoofed ARP replies", TermColor::White)}),
    };
    
    for (int i = 0; i < 5; i++) {
        result.output.push_back(plainLine(randomMAC() + " " + target + " is-at " + randomMAC()));
    }
    
    return result;
}

// ============== EXPLOITATION ==============

CommandResult cmd_msfconsole(const std::vector<std::string>& /*args*/) {
    CommandResult result;
    
    result.output = {
        plainLine(""),
        line({seg("                                                  ", TermColor::White)}),
        line({seg("      .;lxO0KXXK0Oxl:.                            ", TermColor::Red)}),
        line({seg("  .;ok0XXXXXXXKK0kxOOkxo;.                        ", TermColor::Red)}),
        line({seg(" .dXXXXXXXXKK0OOOOOOkkkOOx,                       ", TermColor::Red)}),
        line({seg(" oXXXXXXXXK0OO0000000OOOOOOk.                     ", TermColor::Red)}),
        line({seg(" OXXXXXX0OO0000000000000OOOx                      ", TermColor::Red)}),
        line({seg(" ;XXXX0OOO0000000000000000kl                      ", TermColor::Red)}),
        line({seg("  .kOOOOO0000000000000000x,                       ", TermColor::Red)}),
        line({seg("   .xOOOO000000000000Od;                          ", TermColor::Red)}),
        line({seg("     ':dkO00000Okxl;.                             ", TermColor::Red)}),
        line({seg("         .....                                    ", TermColor::White)}),
        plainLine(""),
        line({seg("       =[ metasploit v6.3.25-dev                  ]", TermColor::Blue)}),
        line({seg("+ -- --=[ ", TermColor::Blue), seg("2345", TermColor::Green), seg(" exploits - ", TermColor::Blue), seg("1234", TermColor::Green), seg(" auxiliary - ", TermColor::Blue), seg("421", TermColor::Green), seg(" post       ]", TermColor::Blue)}),
        line({seg("+ -- --=[ ", TermColor::Blue), seg("956", TermColor::Green), seg(" payloads - ", TermColor::Blue), seg("46", TermColor::Green), seg(" encoders - ", TermColor::Blue), seg("11", TermColor::Green), seg(" nops        ]", TermColor::Blue)}),
        line({seg("+ -- --=[ ", TermColor::Blue), seg("9", TermColor::Green), seg(" evasion                                    ]", TermColor::Blue)}),
        plainLine(""),
        line({seg("Metasploit tip: ", TermColor::Blue), seg("Use help to list all available commands", TermColor::White)}),
        plainLine(""),
        line({seg("msf6 > ", TermColor::Red, true)}),
    };
    
    return result;
}

CommandResult cmd_searchsploit(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("SearchSploit", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: searchsploit [options] term1 [term2] ..."),
            plainLine(""),
            plainLine("  -w     : Show URLs to Exploit-DB.com"),
            plainLine("  -p     : Show full path to exploit"),
            plainLine("  -m     : Mirror (copy) exploit to current dir"),
        };
        return result;
    }
    
    std::string term = args[0];
    
    result.output = {
        line({seg("---------------------------------------------------", TermColor::White)}),
        line({seg(" Exploit Title                     ", TermColor::Red), seg("|  Path", TermColor::Red)}),
        line({seg("---------------------------------------------------", TermColor::White)}),
        plainLine(" " + term + " Buffer Overflow        | exploits/linux/remote/49234.py"),
        plainLine(" " + term + " RCE (Auth)             | exploits/multiple/webapps/48765.rb"),
        plainLine(" " + term + " SQL Injection          | exploits/php/webapps/47892.txt"),
        plainLine(" " + term + " XSS Stored             | exploits/multiple/webapps/46123.html"),
        plainLine(" " + term + " Privilege Escalation   | exploits/linux/local/45678.c"),
        line({seg("---------------------------------------------------", TermColor::White)}),
    };
    
    return result;
}

// ============== PASSWORD CRACKING ==============

CommandResult cmd_hydra(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Hydra v9.4", TermColor::Cyan, true)}),
            plainLine("(c) 2022 by van Hauser/THC & David Maciejak"),
            plainLine(""),
            plainLine("Usage: hydra [[[-l LOGIN|-L FILE] [-p PASS|-P FILE]] | [-C FILE]]"),
            plainLine("              [-e nsr] [-o FILE] [-t TASKS] [-M FILE [-T TASKS]]"),
            plainLine("              [-w TIME] [-W TIME] [-f] [-s PORT] [-x MIN:MAX:CHARSET]"),
            plainLine("              [-c TIME] [-ISOuvVd46] server service [OPT]"),
            plainLine(""),
            plainLine("Examples:"),
            plainLine("  hydra -l admin -P wordlist.txt 192.168.1.1 ssh"),
            plainLine("  hydra -L users.txt -P pass.txt ftp://192.168.1.1"),
        };
        return result;
    }
    
    result.output = {
        line({seg("Hydra v9.4", TermColor::Cyan), seg(" (c) 2022 by van Hauser/THC", TermColor::GrayDark)}),
        plainLine(""),
        line({seg("[DATA] max 16 tasks per 1 server, overall 16 tasks, 14344 login tries", TermColor::White)}),
        line({seg("[DATA] attacking ssh://192.168.1.105:22/", TermColor::White)}),
    };
    
    // Fake attempts
    for (int i = 0; i < 5; i++) {
        result.output.push_back(line({
            seg("[ATTEMPT] target 192.168.1.105 - login \"admin\" - pass \"", TermColor::GrayDark),
            seg(std::to_string(randomInt(10000, 99999)), TermColor::Yellow),
            seg("\" - " + std::to_string(i+1) + " of 14344 [child 0]", TermColor::GrayDark)
        }));
    }
    
    result.output.push_back(plainLine(""));
    result.output.push_back(line({
        seg("[22][ssh] host: 192.168.1.105   login: ", TermColor::Green),
        seg("admin", TermColor::Yellow, true),
        seg("   password: ", TermColor::Green),
        seg("admin123", TermColor::Yellow, true)
    }));
    result.output.push_back(plainLine(""));
    result.output.push_back(line({seg("1 of 1 target successfully completed, 1 valid password found", TermColor::Green)}));
    
    return result;
}

CommandResult cmd_john(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("John the Ripper 1.9.0-jumbo-1", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: john [OPTIONS] [PASSWORD-FILES]"),
            plainLine(""),
            plainLine("  --wordlist=FILE   : Use wordlist mode"),
            plainLine("  --rules           : Enable word mangling rules"),
            plainLine("  --format=NAME     : Force hash type"),
            plainLine("  --show            : Show cracked passwords"),
        };
        return result;
    }
    
    result.output = {
        plainLine("Using default input encoding: UTF-8"),
        plainLine("Loaded 3 password hashes with 3 different salts (sha512crypt)"),
        plainLine("Cost 1 (iteration count) is 5000 for all loaded hashes"),
        plainLine("Will run 8 OpenMP threads"),
        plainLine("Press 'q' or Ctrl-C to abort, almost any other key for status"),
    };
    
    result.output.push_back(line({seg("admin123", TermColor::Green, true), seg("         (admin)", TermColor::White)}));
    result.output.push_back(line({seg("password1", TermColor::Green, true), seg("        (user1)", TermColor::White)}));
    result.output.push_back(line({seg("backup2023", TermColor::Green, true), seg("       (backup)", TermColor::White)}));
    
    result.output.push_back(plainLine("3g 0:00:00:23 DONE 2/3 (0.13g/s 892.4p/s 2456c/s 5123C/s)"));
    result.output.push_back(plainLine("Session completed"));
    
    return result;
}

CommandResult cmd_hashcat(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("hashcat v6.2.6", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: hashcat [options] hash|hashfile [dictionary|mask]"),
            plainLine(""),
            plainLine("  -m <num>   : Hash-type"),
            plainLine("  -a <num>   : Attack-mode (0=dict, 3=brute-force)"),
            plainLine("  -w <num>   : Workload profile"),
            plainLine(""),
            plainLine("Example: hashcat -m 0 -a 0 hash.txt wordlist.txt"),
        };
        return result;
    }
    
    result.output = {
        plainLine("hashcat (v6.2.6) starting"),
        plainLine(""),
        plainLine("OpenCL API (OpenCL 3.0 CUDA) - Platform #1 [NVIDIA]"),
        plainLine("* Device #1: NVIDIA GeForce RTX 3080, 8192/10240 MB, 68MCU"),
        plainLine(""),
        plainLine("Hashes: 1 digests; 1 unique digests, 1 unique salts"),
        plainLine("Bitmaps: 16 bits, 65536 entries, 0x0000ffff mask"),
        plainLine(""),
        line({seg("Status...........: Cracked", TermColor::Green, true)}),
        plainLine("Hash.Name........: MD5"),
        plainLine("Hash.Target......: 5f4dcc3b5aa765d61d8327deb882cf99"),
        line({seg("Recovered........: 1/1 (100.00%)", TermColor::Green)}),
        plainLine(""),
        line({seg("5f4dcc3b5aa765d61d8327deb882cf99:password", TermColor::Green, true)}),
        plainLine(""),
        plainLine("Session..........: hashcat"),
        plainLine("Status...........: Cracked"),
        plainLine("Time.Started.....: " + currentTimestamp()),
        plainLine("Speed.#1.........: 12345.6 MH/s"),
    };
    
    return result;
}

// ============== WEB SCANNING ==============

CommandResult cmd_nikto(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Nikto v2.5.0", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: nikto -h <target> [options]"),
            plainLine(""),
            plainLine("  -h <host>    : Target host"),
            plainLine("  -p <port>    : Target port"),
            plainLine("  -ssl         : Use SSL"),
            plainLine("  -o <file>    : Output file"),
        };
        return result;
    }
    
    std::string target = args.size() > 1 ? args[1] : "192.168.1.100";
    
    result.output = {
        line({seg("- Nikto v2.5.0", TermColor::Cyan)}),
        plainLine("---------------------------------------------------------------------------"),
        plainLine("+ Target IP:          " + target),
        plainLine("+ Target Hostname:    " + target),
        plainLine("+ Target Port:        80"),
        plainLine("+ Start Time:         " + currentTimestamp()),
        plainLine("---------------------------------------------------------------------------"),
        plainLine("+ Server: Apache/2.4.54 (Ubuntu)"),
        line({seg("+ /: The anti-clickjacking X-Frame-Options header is not present.", TermColor::Yellow)}),
        line({seg("+ /: The X-Content-Type-Options header is not set.", TermColor::Yellow)}),
        line({seg("+ /admin/: Directory indexing found.", TermColor::Red)}),
        line({seg("+ /backup/: Backup directory found.", TermColor::Red)}),
        line({seg("+ /phpinfo.php: PHP Info page found.", TermColor::Red)}),
        line({seg("+ /config.php.bak: Config backup file found.", TermColor::Red)}),
        plainLine("+ " + std::to_string(randomInt(20, 50)) + " requests: 0 error(s) and " + std::to_string(randomInt(5, 15)) + " item(s) reported"),
        plainLine("+ End Time:           " + currentTimestamp()),
        plainLine("---------------------------------------------------------------------------"),
    };
    
    return result;
}

CommandResult cmd_sqlmap(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("sqlmap 1.7.2", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: sqlmap [options]"),
            plainLine(""),
            plainLine("Target:"),
            plainLine("  -u URL      : Target URL"),
            plainLine("  -r FILE     : Load HTTP request from file"),
            plainLine(""),
            plainLine("Detection:"),
            plainLine("  --level     : Level of tests (1-5)"),
            plainLine("  --risk      : Risk of tests (1-3)"),
        };
        return result;
    }
    
    result.output = {
        line({seg("        ___", TermColor::Red)}),
        line({seg("       __H__", TermColor::Red)}),
        line({seg(" ___ ___[,]_____ ___ ___  ", TermColor::Red), seg("{1.7.2#stable}", TermColor::Yellow)}),
        line({seg("|_ -| . [']     | .'| . |", TermColor::Red)}),
        line({seg("|___|_  [)]_|_|_|__,|  _|", TermColor::Red)}),
        line({seg("      |_|V...       |_|  ", TermColor::Red), seg("https://sqlmap.org", TermColor::Cyan)}),
        plainLine(""),
        plainLine("[*] starting @ " + currentTimestamp()),
        plainLine(""),
        line({seg("[INFO] testing connection to the target URL", TermColor::Green)}),
        line({seg("[INFO] testing if the target URL content is stable", TermColor::Green)}),
        line({seg("[INFO] target URL content is stable", TermColor::Green)}),
        line({seg("[INFO] testing if GET parameter 'id' is dynamic", TermColor::Green)}),
        line({seg("[WARNING] GET parameter 'id' does not appear to be dynamic", TermColor::Yellow)}),
        line({seg("[INFO] heuristic (basic) test shows that GET parameter 'id' might be injectable", TermColor::Green)}),
        plainLine(""),
        line({seg("[INFO] GET parameter 'id' appears to be 'MySQL >= 5.0 AND error-based' injectable", TermColor::Green, true)}),
        plainLine(""),
        plainLine("sqlmap identified the following injection point(s):"),
        plainLine("---"),
        plainLine("Parameter: id (GET)"),
        plainLine("    Type: error-based"),
        plainLine("    Title: MySQL >= 5.0 AND error-based"),
        plainLine("---"),
        line({seg("[INFO] the back-end DBMS is MySQL", TermColor::Green)}),
        plainLine("back-end DBMS: MySQL >= 5.0"),
    };
    
    return result;
}

CommandResult cmd_dirb(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("DIRB v2.22", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage: dirb <url_base> [wordlist] [options]"),
            plainLine(""),
            plainLine("Options:"),
            plainLine("  -o <file>  : Output to file"),
            plainLine("  -r         : Don't search recursively"),
            plainLine("  -z <ms>    : Add delay between requests"),
        };
        return result;
    }
    
    std::string target = args[0];
    
    result.output = {
        plainLine("-----------------"),
        line({seg("DIRB v2.22", TermColor::Cyan)}),
        plainLine("By The Dark Raver"),
        plainLine("-----------------"),
        plainLine(""),
        plainLine("START_TIME: " + currentTimestamp()),
        plainLine("URL_BASE: " + target),
        plainLine("WORDLIST_FILES: /usr/share/dirb/wordlists/common.txt"),
        plainLine(""),
        plainLine("-----------------"),
        plainLine(""),
        plainLine("GENERATED WORDS: 4612"),
        plainLine(""),
        line({seg("---- Scanning URL: " + target + " ----", TermColor::Yellow)}),
        line({seg("+ " + target + "/admin (CODE:301|SIZE:310)", TermColor::Green)}),
        line({seg("+ " + target + "/backup (CODE:301|SIZE:311)", TermColor::Green)}),
        line({seg("+ " + target + "/config (CODE:403|SIZE:277)", TermColor::Red)}),
        line({seg("+ " + target + "/index.php (CODE:200|SIZE:1234)", TermColor::Green)}),
        line({seg("+ " + target + "/login (CODE:200|SIZE:892)", TermColor::Green)}),
        line({seg("+ " + target + "/uploads (CODE:301|SIZE:313)", TermColor::Green)}),
        plainLine(""),
        plainLine("-----------------"),
        plainLine("END_TIME: " + currentTimestamp()),
        plainLine("DOWNLOADED: 4612 - FOUND: 6"),
    };
    
    return result;
}

CommandResult cmd_gobuster(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            line({seg("Gobuster v3.5", TermColor::Cyan, true)}),
            plainLine(""),
            plainLine("Usage:"),
            plainLine("  gobuster dir -u <url> -w <wordlist>"),
            plainLine("  gobuster dns -d <domain> -w <wordlist>"),
            plainLine("  gobuster vhost -u <url> -w <wordlist>"),
        };
        return result;
    }
    
    result.output = {
        line({seg("===============================================================", TermColor::Cyan)}),
        line({seg("Gobuster v3.5", TermColor::Cyan)}),
        line({seg("===============================================================", TermColor::Cyan)}),
        plainLine("[+] Url:            http://192.168.1.100"),
        plainLine("[+] Method:         GET"),
        plainLine("[+] Threads:        10"),
        plainLine("[+] Wordlist:       /usr/share/wordlists/dirb/common.txt"),
        plainLine("[+] Status codes:   200,204,301,302,307,401,403"),
        plainLine("[+] Timeout:        10s"),
        line({seg("===============================================================", TermColor::Cyan)}),
        plainLine("Starting gobuster in directory enumeration mode"),
        line({seg("===============================================================", TermColor::Cyan)}),
        line({seg("/admin               (Status: 301) [Size: 310]", TermColor::Green)}),
        line({seg("/api                 (Status: 301) [Size: 307]", TermColor::Green)}),
        line({seg("/backup              (Status: 301) [Size: 311]", TermColor::Green)}),
        line({seg("/config              (Status: 403) [Size: 277]", TermColor::Yellow)}),
        line({seg("/images              (Status: 301) [Size: 311]", TermColor::Green)}),
        line({seg("/js                  (Status: 301) [Size: 306]", TermColor::Green)}),
        line({seg("/uploads             (Status: 301) [Size: 313]", TermColor::Green)}),
        line({seg("===============================================================", TermColor::Cyan)}),
        plainLine("Finished"),
    };
    
    return result;
}

// ============== OTHER RECON ==============

CommandResult cmd_whois(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {plainLine("Usage: whois <domain>")};
        return result;
    }
    
    std::string domain = args[0];
    
    result.output = {
        plainLine("Domain Name: " + domain),
        plainLine("Registry Domain ID: 123456789_DOMAIN"),
        plainLine("Registrar WHOIS Server: whois.registrar.com"),
        plainLine("Registrar URL: http://www.registrar.com"),
        plainLine("Updated Date: 2024-01-15T12:00:00Z"),
        plainLine("Creation Date: 2015-03-20T10:30:00Z"),
        plainLine("Registry Expiry Date: 2025-03-20T10:30:00Z"),
        plainLine("Registrar: Example Registrar Inc."),
        plainLine(""),
        plainLine("Registrant Name: REDACTED FOR PRIVACY"),
        plainLine("Registrant Organization: Example Corp"),
        plainLine("Registrant Country: US"),
        plainLine(""),
        plainLine("Name Server: ns1.example.com"),
        plainLine("Name Server: ns2.example.com"),
        plainLine("DNSSEC: unsigned"),
    };
    
    return result;
}

CommandResult cmd_dig(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {plainLine("Usage: dig [@server] <name> [type]")};
        return result;
    }
    
    std::string domain = args[0];
    
    result.output = {
        plainLine("; <<>> DiG 9.18.12 <<>> " + domain),
        plainLine(";; global options: +cmd"),
        plainLine(";; Got answer:"),
        plainLine(";; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: " + std::to_string(randomInt(10000, 65535))),
        plainLine(";; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 0, ADDITIONAL: 1"),
        plainLine(""),
        plainLine(";; QUESTION SECTION:"),
        plainLine(";" + domain + ".\t\t\tIN\tA"),
        plainLine(""),
        plainLine(";; ANSWER SECTION:"),
        plainLine(domain + ".\t\t300\tIN\tA\t" + randomIP()),
        plainLine(domain + ".\t\t300\tIN\tA\t" + randomIP()),
        plainLine(""),
        plainLine(";; Query time: " + std::to_string(randomInt(10, 100)) + " msec"),
        plainLine(";; SERVER: 8.8.8.8#53(8.8.8.8) (UDP)"),
        plainLine(";; WHEN: " + currentTimestamp()),
        plainLine(";; MSG SIZE  rcvd: 89"),
    };
    
    return result;
}

CommandResult cmd_traceroute(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {plainLine("Usage: traceroute <host>")};
        return result;
    }
    
    std::string target = args[0];
    
    result.output = {
        plainLine("traceroute to " + target + ", 30 hops max, 60 byte packets"),
    };
    
    int hops = randomInt(8, 15);
    for (int i = 1; i <= hops; i++) {
        std::stringstream ss;
        ss << std::setw(2) << i << "  ";
        
        if (i == 1) {
            ss << "192.168.1.1  " << randomInt(1, 5) << "." << randomInt(100, 999) << " ms";
        } else if (i == hops) {
            ss << target << "  " << randomInt(20, 100) << "." << randomInt(100, 999) << " ms";
        } else {
            ss << randomIP() << "  " << randomInt(5, 50) << "." << randomInt(100, 999) << " ms";
        }
        
        result.output.push_back(plainLine(ss.str()));
    }
    
    return result;
}

CommandResult cmd_curl(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {plainLine("Usage: curl [options] <url>")};
        return result;
    }
    
    result.output = {
        plainLine("<!DOCTYPE html>"),
        plainLine("<html>"),
        plainLine("<head><title>Index</title></head>"),
        plainLine("<body>"),
        plainLine("<h1>Welcome</h1>"),
        plainLine("<p>Server response from " + args[0] + "</p>"),
        plainLine("</body>"),
        plainLine("</html>"),
    };
    
    return result;
}

CommandResult cmd_wget(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {plainLine("Usage: wget [options] <url>")};
        return result;
    }
    
    std::string url = args[0];
    
    result.output = {
        plainLine("--" + currentTimestamp() + "--  " + url),
        plainLine("Resolving " + url + "... " + randomIP()),
        plainLine("Connecting to " + url + "|" + randomIP() + "|:80... connected."),
        plainLine("HTTP request sent, awaiting response... 200 OK"),
        plainLine("Length: " + std::to_string(randomInt(1000, 50000)) + " (" + std::to_string(randomInt(1, 50)) + "K) [text/html]"),
        plainLine("Saving to: 'index.html'"),
        plainLine(""),
        line({seg("index.html              100%[=======================>]   ", TermColor::White), seg(std::to_string(randomInt(1, 50)) + "K", TermColor::Green), seg("  in 0." + std::to_string(randomInt(1, 9)) + "s", TermColor::White)}),
        plainLine(""),
        plainLine(currentTimestamp() + " - 'index.html' saved"),
    };
    
    return result;
}

// ============== SSH / CONNECTIONS ==============

CommandResult cmd_ssh(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine("usage: ssh [-46AaCfGgKkMNnqsTtVvXxYy] [-B bind_interface]"),
            plainLine("           [-b bind_address] [-c cipher_spec] [-D [bind_address:]port]"),
            plainLine("           [-E log_file] [-e escape_char] [-F configfile]"),
            plainLine("           [-i identity_file] [-L address] [-l login_name]"),
            plainLine("           destination [command]"),
        };
        return result;
    }
    
    std::string target = args[0];
    
    result.output = {
        line({seg("The authenticity of host '" + target + "' can't be established.", TermColor::Yellow)}),
        plainLine("ED25519 key fingerprint is SHA256:" + randomMAC().substr(0, 8) + randomMAC().substr(0, 8) + randomMAC().substr(0, 8)),
        line({seg("Are you sure you want to continue connecting (yes/no/[fingerprint])? ", TermColor::Yellow), seg("yes", TermColor::Green)}),
        plainLine("Warning: Permanently added '" + target + "' (ED25519) to the list of known hosts."),
        plainLine(""),
        line({seg("Connection established to " + target, TermColor::Green)}),
        plainLine("Last login: " + currentTimestamp() + " from " + randomIP()),
        plainLine(""),
    };
    
    return result;
}

CommandResult cmd_nc(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {
            plainLine(""),
            plainLine("Usage: nc [options] [hostname] [port]"),
            plainLine(""),
            plainLine("Options:"),
            plainLine("  -l          : Listen mode"),
            plainLine("  -p port     : Local port"),
            plainLine("  -e prog     : Program to exec after connect"),
            plainLine("  -v          : Verbose"),
            plainLine("  -z          : Zero-I/O mode (scanning)"),
        };
        return result;
    }
    
    bool listen = false;
    for (const auto& arg : args) {
        if (arg == "-l" || arg == "-lp" || arg == "-lvp") {
            listen = true;
            break;
        }
    }
    
    if (listen) {
        result.output = {
            plainLine("listening on [0.0.0.0] " + (args.size() > 1 ? args.back() : "4444") + " ..."),
            line({seg("connect to [192.168.1.105] from " + randomIP() + " [" + randomIP() + "] " + std::to_string(randomInt(40000, 60000)), TermColor::Green)}),
        };
    } else {
        result.output = {
            line({seg("Connection to " + args[0] + " " + (args.size() > 1 ? args[1] : "80") + " port [tcp/*] succeeded!", TermColor::Green)}),
        };
    }
    
    return result;
}

} // namespace hacksim

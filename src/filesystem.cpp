#include "../include/filesystem.hpp"
#include "../include/terminal.hpp"
#include "../include/utils.hpp"

#include <sstream>
#include <iomanip>

namespace hacksim {

FileSystem& FileSystem::instance() {
    static FileSystem fs;
    return fs;
}

FileSystem::FileSystem() {
    initializeFS();
}

void FileSystem::initializeFS() {
    root_.name = "/";
    root_.is_directory = true;
    root_.permissions = "drwxr-xr-x";
    
    // /home
    FileNode home;
    home.name = "home";
    home.is_directory = true;
    home.permissions = "drwxr-xr-x";
    
    // /home/root
    FileNode root_home;
    root_home.name = "root";
    root_home.is_directory = true;
    root_home.permissions = "drwx------";
    
    // Files in /home/root
    FileNode bashrc;
    bashrc.name = ".bashrc";
    bashrc.content = "# ~/.bashrc: executed by bash(1) for non-login shells.\nexport PS1='\\[\\033[01;32m\\]\\u@\\h\\[\\033[00m\\]:\\[\\033[01;34m\\]\\w\\[\\033[00m\\]\\$ '\nalias ls='ls --color=auto'\nalias ll='ls -la'\n";
    bashrc.size = bashrc.content.size();
    root_home.children.push_back(bashrc);
    
    FileNode targets;
    targets.name = "targets.txt";
    targets.content = "# Target list - CONFIDENTIAL\n192.168.1.1     gateway\n192.168.1.100   fileserver\n192.168.1.101   webserver\n10.0.0.50       database\n172.16.0.1      firewall\n";
    targets.size = targets.content.size();
    root_home.children.push_back(targets);
    
    FileNode credentials;
    credentials.name = "credentials.db";
    credentials.content = "admin:$6$rounds=5000$salt$hashed_password_here\nuser1:$6$rounds=5000$salt$another_hash_here\nbackup:$6$rounds=5000$salt$backup_service_hash\n";
    credentials.size = credentials.content.size();
    credentials.permissions = "-rw-------";
    root_home.children.push_back(credentials);
    
    FileNode notes;
    notes.name = "notes.txt";
    notes.content = "TODO:\n- Scan subnet 192.168.1.0/24\n- Check for vulnerable services\n- Review firewall rules\n- Update metasploit modules\n\nRemember: Leave no traces.\n";
    notes.size = notes.content.size();
    root_home.children.push_back(notes);
    
    // Tools directory
    FileNode tools;
    tools.name = "tools";
    tools.is_directory = true;
    tools.permissions = "drwxr-xr-x";
    
    FileNode exploit;
    exploit.name = "exploit.py";
    exploit.content = "#!/usr/bin/env python3\n# CVE-2024-XXXX Exploit\nimport socket\nimport struct\n\ndef exploit(target, port):\n    payload = b'\\x90' * 100  # NOP sled\n    payload += shellcode\n    # ... exploit code ...\n";
    exploit.size = exploit.content.size();
    exploit.permissions = "-rwxr-xr-x";
    tools.children.push_back(exploit);
    
    FileNode scanner;
    scanner.name = "scanner.sh";
    scanner.content = "#!/bin/bash\n# Quick network scanner\nfor ip in $(seq 1 254); do\n    ping -c 1 -W 1 192.168.1.$ip &>/dev/null && echo \"192.168.1.$ip is up\"\ndone\n";
    scanner.size = scanner.content.size();
    scanner.permissions = "-rwxr-xr-x";
    tools.children.push_back(scanner);
    
    root_home.children.push_back(tools);
    
    // Loot directory
    FileNode loot;
    loot.name = "loot";
    loot.is_directory = true;
    loot.permissions = "drwx------";
    
    FileNode dump;
    dump.name = "database_dump.sql";
    dump.content = "-- MySQL dump\n-- Server version: 8.0.32\n\nCREATE TABLE users (\n  id INT PRIMARY KEY,\n  username VARCHAR(50),\n  password_hash VARCHAR(255),\n  email VARCHAR(100)\n);\n\nINSERT INTO users VALUES\n(1, 'admin', '$2y$10$abcdef...', 'admin@corp.local'),\n(2, 'jsmith', '$2y$10$ghijkl...', 'j.smith@corp.local');\n";
    dump.size = dump.content.size();
    loot.children.push_back(dump);
    
    root_home.children.push_back(loot);
    
    home.children.push_back(root_home);
    root_.children.push_back(home);
    
    // /etc
    FileNode etc;
    etc.name = "etc";
    etc.is_directory = true;
    etc.permissions = "drwxr-xr-x";
    
    FileNode passwd;
    passwd.name = "passwd";
    passwd.content = "root:x:0:0:root:/root:/bin/bash\ndaemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin\nbin:x:2:2:bin:/bin:/usr/sbin/nologin\nwww-data:x:33:33:www-data:/var/www:/usr/sbin/nologin\npostgres:x:117:125:PostgreSQL administrator,,,:/var/lib/postgresql:/bin/bash\n";
    passwd.size = passwd.content.size();
    etc.children.push_back(passwd);
    
    FileNode shadow;
    shadow.name = "shadow";
    shadow.content = "root:$6$xyz$longhash...:19500:0:99999:7:::\ndaemon:*:19500:0:99999:7:::\nwww-data:*:19500:0:99999:7:::\npostgres:$6$abc$anotherhash...:19500:0:99999:7:::\n";
    shadow.size = shadow.content.size();
    shadow.permissions = "-rw-r-----";
    shadow.owner = "root";
    shadow.group = "shadow";
    etc.children.push_back(shadow);
    
    root_.children.push_back(etc);
    
    // /var
    FileNode var;
    var.name = "var";
    var.is_directory = true;
    var.permissions = "drwxr-xr-x";
    
    FileNode log;
    log.name = "log";
    log.is_directory = true;
    log.permissions = "drwxr-xr-x";
    
    FileNode authlog;
    authlog.name = "auth.log";
    authlog.content = "Dec  5 03:14:22 kali sshd[1234]: Accepted publickey for root from 192.168.1.1 port 54321\nDec  5 03:14:22 kali sshd[1234]: pam_unix(sshd:session): session opened for user root\nDec  5 03:15:01 kali CRON[1337]: pam_unix(cron:session): session opened for user root\nDec  5 03:22:47 kali sudo: root : TTY=pts/0 ; PWD=/root ; USER=root ; COMMAND=/usr/bin/nmap\n";
    authlog.size = authlog.content.size();
    log.children.push_back(authlog);
    
    var.children.push_back(log);
    root_.children.push_back(var);
}

FileNode* FileSystem::getCurrentNode() {
    return findNode(current_path_);
}

FileNode* FileSystem::findNode(const std::string& path) {
    if (path == "/" || path.empty()) {
        return &root_;
    }
    
    std::string clean_path = path;
    if (clean_path[0] == '/') {
        clean_path = clean_path.substr(1);
    }
    
    auto parts = split(clean_path, '/');
    FileNode* current = &root_;
    
    for (const auto& part : parts) {
        if (part.empty() || part == ".") continue;
        
        bool found = false;
        for (auto& child : current->children) {
            if (child.name == part) {
                current = &child;
                found = true;
                break;
            }
        }
        if (!found) {
            return nullptr;
        }
    }
    
    return current;
}

std::vector<ColoredLine> FileSystem::ls(const std::string& path, bool long_format) {
    std::vector<ColoredLine> result;
    
    FileNode* node = path.empty() ? getCurrentNode() : findNode(path);
    if (!node) {
        result.push_back(line({seg("ls: cannot access '" + path + "': No such file or directory", TermColor::Red)}));
        return result;
    }
    
    if (!node->is_directory) {
        if (long_format) {
            std::stringstream ss;
            ss << node->permissions << " 1 " << node->owner << " " << node->group;
            ss << " " << std::setw(6) << node->size << " Dec  5 03:14 ";
            result.push_back(line({seg(ss.str()), seg(node->name)}));
        } else {
            result.push_back(plainLine(node->name));
        }
        return result;
    }
    
    if (long_format) {
        result.push_back(plainLine("total " + std::to_string(node->children.size() * 4)));
    }
    
    for (const auto& child : node->children) {
        if (long_format) {
            std::stringstream ss;
            ss << child.permissions << " 1 " << child.owner << " " << child.group;
            ss << " " << std::setw(6) << child.size << " Dec  5 03:14 ";
            
            if (child.is_directory) {
                result.push_back(line({seg(ss.str()), seg(child.name, TermColor::Blue, true)}));
            } else if (child.permissions[3] == 'x') {
                result.push_back(line({seg(ss.str()), seg(child.name, TermColor::Green)}));
            } else {
                result.push_back(line({seg(ss.str()), seg(child.name)}));
            }
        } else {
            if (child.is_directory) {
                result.push_back(line({seg(child.name, TermColor::Blue, true)}));
            } else if (child.permissions[3] == 'x') {
                result.push_back(line({seg(child.name, TermColor::Green)}));
            } else {
                result.push_back(plainLine(child.name));
            }
        }
    }
    
    return result;
}

std::vector<ColoredLine> FileSystem::cat(const std::string& filename) {
    std::vector<ColoredLine> result;
    
    std::string full_path = filename;
    if (filename[0] != '/') {
        full_path = current_path_ + "/" + filename;
    }
    
    FileNode* node = findNode(full_path);
    if (!node) {
        result.push_back(line({seg("cat: " + filename + ": No such file or directory", TermColor::Red)}));
        return result;
    }
    
    if (node->is_directory) {
        result.push_back(line({seg("cat: " + filename + ": Is a directory", TermColor::Red)}));
        return result;
    }
    
    auto lines_vec = split(node->content, '\n');
    for (const auto& l : lines_vec) {
        result.push_back(plainLine(l));
    }
    
    return result;
}

bool FileSystem::cd(const std::string& path) {
    std::string new_path;
    
    if (path.empty() || path == "~") {
        new_path = "/home/root";
    } else if (path == "..") {
        size_t pos = current_path_.rfind('/');
        if (pos == 0) {
            new_path = "/";
        } else if (pos != std::string::npos) {
            new_path = current_path_.substr(0, pos);
        } else {
            new_path = "/";
        }
    } else if (path[0] == '/') {
        new_path = path;
    } else {
        new_path = current_path_ + "/" + path;
    }
    
    FileNode* node = findNode(new_path);
    if (!node) {
        return false;
    }
    
    if (!node->is_directory) {
        return false;
    }
    
    current_path_ = new_path;
    return true;
}

std::string FileSystem::pwd() const {
    return current_path_;
}

// Command implementations

CommandResult cmd_ls(const std::vector<std::string>& args) {
    CommandResult result;
    bool long_format = false;
    std::string path;
    
    for (const auto& arg : args) {
        if (arg == "-l" || arg == "-la" || arg == "-al") {
            long_format = true;
        } else if (arg[0] != '-') {
            path = arg;
        }
    }
    
    result.output = FileSystem::instance().ls(path, long_format);
    return result;
}

CommandResult cmd_cat(const std::vector<std::string>& args) {
    CommandResult result;
    
    if (args.empty()) {
        result.output = {line({seg("cat: missing operand", TermColor::Red)})};
        result.success = false;
        return result;
    }
    
    result.output = FileSystem::instance().cat(args[0]);
    return result;
}

CommandResult cmd_cd(const std::vector<std::string>& args) {
    CommandResult result;
    
    std::string path = args.empty() ? "~" : args[0];
    
    if (!FileSystem::instance().cd(path)) {
        result.output = {line({seg("cd: " + path + ": No such file or directory", TermColor::Red)})};
        result.success = false;
    }
    
    return result;
}

} // namespace hacksim

#pragma once

#include "terminal.hpp"
#include <string>
#include <vector>

namespace hacksim {

struct FileNode {
    std::string name;
    bool is_directory = false;
    std::string content;
    std::string permissions = "-rw-r--r--";
    std::string owner = "root";
    std::string group = "root";
    int size = 0;
    std::vector<FileNode> children;
};

class FileSystem {
public:
    static FileSystem& instance();
    
    std::vector<ColoredLine> ls(const std::string& path, bool long_format = false);
    std::vector<ColoredLine> cat(const std::string& filename);
    bool cd(const std::string& path);
    std::string pwd() const;
    
private:
    FileSystem();
    void initializeFS();
    FileNode* findNode(const std::string& path);
    FileNode* getCurrentNode();
    
    FileNode root_;
    std::string current_path_ = "/home/root";
};

CommandResult cmd_ls(const std::vector<std::string>& args);
CommandResult cmd_cat(const std::vector<std::string>& args);
CommandResult cmd_cd(const std::vector<std::string>& args);

} // namespace hacksim

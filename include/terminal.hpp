#pragma once

#include <string>
#include <vector>

namespace hacksim {

// Color enum for terminal output
enum class TermColor {
    Default,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    GrayDark
};

// Text segment with color
struct TextSegment {
    std::string text;
    TermColor color = TermColor::Default;
    bool bold = false;
};

// A line is made of segments
using ColoredLine = std::vector<TextSegment>;

struct CommandResult {
    std::vector<ColoredLine> output;
    bool success = true;
    bool should_exit = false;
    bool clear_screen = false;
};

// Helper functions to create colored segments
TextSegment seg(const std::string& text, TermColor color = TermColor::Default, bool bold = false);
ColoredLine line(std::initializer_list<TextSegment> segments);
ColoredLine plainLine(const std::string& text);

class Terminal {
public:
    Terminal();
    void run();
    
private:
    std::string current_user_ = "root";
    std::string current_host_ = "kali";
    std::string current_dir_ = "~";
    std::vector<std::string> history_;
    std::vector<ColoredLine> output_buffer_;
    int history_index_ = -1;  // -1 means not browsing history
    int scroll_offset_ = 0;   // 0 means at bottom (latest)
    
    ColoredLine getPromptLine() const;
    CommandResult executeCommand(const std::string& input);
    void addToOutput(const std::vector<ColoredLine>& lines);
    void addToOutput(const ColoredLine& line);
};

} // namespace hacksim

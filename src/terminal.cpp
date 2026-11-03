#include "../include/terminal.hpp"
#include "../include/commands.hpp"
#include "../include/filesystem.hpp"
#include "../include/nmap.hpp"
#include "../include/tools.hpp"
#include "../include/htop.hpp"
#include "../include/utils.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

namespace hacksim {

// Helper function implementations
TextSegment seg(const std::string& text, TermColor color, bool bold) {
    return TextSegment{text, color, bold};
}

ColoredLine line(std::initializer_list<TextSegment> segments) {
    return ColoredLine(segments);
}

ColoredLine plainLine(const std::string& text) {
    return ColoredLine{TextSegment{text, TermColor::Default, false}};
}

// Convert TermColor enum to FTXUI color
ftxui::Color toFtxuiColor(TermColor c) {
    switch (c) {
        case TermColor::Red: return ftxui::Color::Red;
        case TermColor::Green: return ftxui::Color::Green;
        case TermColor::Yellow: return ftxui::Color::Yellow;
        case TermColor::Blue: return ftxui::Color::Blue;
        case TermColor::Magenta: return ftxui::Color::Magenta;
        case TermColor::Cyan: return ftxui::Color::Cyan;
        case TermColor::White: return ftxui::Color::White;
        case TermColor::GrayDark: return ftxui::Color::GrayDark;
        default: return ftxui::Color::Default;
    }
}

// Convert ColoredLine to FTXUI Element
ftxui::Element toElement(const ColoredLine& cline) {
    using namespace ftxui;
    Elements elements;
    
    for (const auto& segment : cline) {
        auto el = text(segment.text);
        if (segment.color != TermColor::Default) {
            el = el | color(toFtxuiColor(segment.color));
        }
        if (segment.bold) {
            el = el | bold;
        }
        elements.push_back(el);
    }
    
    if (elements.empty()) {
        return text("");
    }
    
    return hbox(elements);
}

Terminal::Terminal() {
    // Startup banner
    output_buffer_.push_back(plainLine(""));
    output_buffer_.push_back(line({seg("    ██╗  ██╗ █████╗  ██████╗██╗  ██╗███████╗██╗███╗   ███╗", TermColor::Green)}));
    output_buffer_.push_back(line({seg("    ██║  ██║██╔══██╗██╔════╝██║ ██╔╝██╔════╝██║████╗ ████║", TermColor::Green)}));
    output_buffer_.push_back(line({seg("    ███████║███████║██║     █████╔╝ ███████╗██║██╔████╔██║", TermColor::Green)}));
    output_buffer_.push_back(line({seg("    ██╔══██║██╔══██║██║     ██╔═██╗ ╚════██║██║██║╚██╔╝██║", TermColor::Green)}));
    output_buffer_.push_back(line({seg("    ██║  ██║██║  ██║╚██████╗██║  ██╗███████║██║██║ ╚═╝ ██║", TermColor::Green)}));
    output_buffer_.push_back(line({seg("    ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝╚═╝     ╚═╝", TermColor::Green)}));
    output_buffer_.push_back(plainLine(""));
    output_buffer_.push_back(line({seg("    Hacker Terminal Simulator v1.0.0", TermColor::GrayDark)}));
    output_buffer_.push_back(line({seg("    Type 'help' for available commands.", TermColor::GrayDark)}));
    output_buffer_.push_back(plainLine(""));
}

ColoredLine Terminal::getPromptLine() const {
    ColoredLine prompt;
    prompt.push_back(seg(current_user_ + "@" + current_host_, TermColor::Green, true));
    prompt.push_back(seg(":"));
    prompt.push_back(seg(current_dir_, TermColor::Blue, true));
    if (current_user_ == "root") {
        prompt.push_back(seg("# "));
    } else {
        prompt.push_back(seg("$ "));
    }
    return prompt;
}

void Terminal::addToOutput(const ColoredLine& ln) {
    output_buffer_.push_back(ln);
}

void Terminal::addToOutput(const std::vector<ColoredLine>& lines) {
    for (const auto& ln : lines) {
        output_buffer_.push_back(ln);
    }
}

CommandResult Terminal::executeCommand(const std::string& input) {
    CommandResult result;
    
    std::string trimmed = trim(input);
    if (trimmed.empty()) {
        return result;
    }
    
    history_.push_back(trimmed);
    
    auto args = split(trimmed);
    if (args.empty()) {
        return result;
    }
    
    std::string cmd = args[0];
    std::vector<std::string> cmd_args(args.begin() + 1, args.end());
    
    if (cmd == "help") {
        result = cmd_help(cmd_args);
    } else if (cmd == "clear") {
        result = cmd_clear(cmd_args);
    } else if (cmd == "exit" || cmd == "quit") {
        result = cmd_exit(cmd_args);
    } else if (cmd == "whoami") {
        result = cmd_whoami(cmd_args);
    } else if (cmd == "id") {
        result = cmd_id(cmd_args);
    } else if (cmd == "uname") {
        result = cmd_uname(cmd_args);
    } else if (cmd == "hostname") {
        result = cmd_hostname(cmd_args);
    } else if (cmd == "pwd") {
        result = cmd_pwd(cmd_args);
    } else if (cmd == "ls" || cmd == "dir") {
        result = cmd_ls(cmd_args);
    } else if (cmd == "cat") {
        result = cmd_cat(cmd_args);
    } else if (cmd == "cd") {
        result = cmd_cd(cmd_args);
    } else if (cmd == "ps") {
        result = cmd_ps(cmd_args);
    } else if (cmd == "netstat") {
        result = cmd_netstat(cmd_args);
    } else if (cmd == "ifconfig" || cmd == "ip") {
        result = cmd_ifconfig(cmd_args);
    } else if (cmd == "date") {
        result = cmd_date(cmd_args);
    } else if (cmd == "uptime") {
        result = cmd_uptime(cmd_args);
    } else if (cmd == "nmap") {
        result = cmd_nmap_simple(cmd_args);
    }
    // WiFi hacking
    else if (cmd == "airmon-ng") {
        result = cmd_airmon(cmd_args);
    } else if (cmd == "airodump-ng") {
        result = cmd_airodump(cmd_args);
    } else if (cmd == "aireplay-ng") {
        result = cmd_aireplay(cmd_args);
    } else if (cmd == "aircrack-ng") {
        result = cmd_aircrack(cmd_args);
    }
    // Packet sniffing
    else if (cmd == "tcpdump") {
        result = cmd_tcpdump(cmd_args);
    } else if (cmd == "tshark" || cmd == "wireshark") {
        result = cmd_tshark(cmd_args);
    }
    // MITM
    else if (cmd == "ettercap") {
        result = cmd_ettercap(cmd_args);
    } else if (cmd == "arpspoof") {
        result = cmd_arpspoof(cmd_args);
    }
    // Exploitation
    else if (cmd == "msfconsole" || cmd == "msf" || cmd == "metasploit") {
        result = cmd_msfconsole(cmd_args);
    } else if (cmd == "searchsploit") {
        result = cmd_searchsploit(cmd_args);
    }
    // Password cracking
    else if (cmd == "hydra") {
        result = cmd_hydra(cmd_args);
    } else if (cmd == "john") {
        result = cmd_john(cmd_args);
    } else if (cmd == "hashcat") {
        result = cmd_hashcat(cmd_args);
    }
    // Web scanning
    else if (cmd == "nikto") {
        result = cmd_nikto(cmd_args);
    } else if (cmd == "sqlmap") {
        result = cmd_sqlmap(cmd_args);
    } else if (cmd == "dirb") {
        result = cmd_dirb(cmd_args);
    } else if (cmd == "gobuster") {
        result = cmd_gobuster(cmd_args);
    }
    // Recon
    else if (cmd == "whois") {
        result = cmd_whois(cmd_args);
    } else if (cmd == "dig") {
        result = cmd_dig(cmd_args);
    } else if (cmd == "traceroute") {
        result = cmd_traceroute(cmd_args);
    } else if (cmd == "curl") {
        result = cmd_curl(cmd_args);
    } else if (cmd == "wget") {
        result = cmd_wget(cmd_args);
    }
    // Connections
    else if (cmd == "ssh") {
        result = cmd_ssh(cmd_args);
    } else if (cmd == "nc" || cmd == "netcat") {
        result = cmd_nc(cmd_args);
    }
    // htop - special interactive mode
    else if (cmd == "htop" || cmd == "top") {
        // htop runs in its own screen, so we return empty and handle separately
        run_htop([]() { return false; });
        return result;
    }
    else {
        result.output.push_back(line({
            seg("bash: " + cmd + ": command not found", TermColor::Red)
        }));
        result.success = false;
    }
    
    return result;
}

void Terminal::run() {
    using namespace ftxui;
    
    auto screen = ScreenInteractive::Fullscreen();
    
    std::string input_content;
    std::string saved_input;  // Save current input when browsing history
    
    auto input_option = InputOption();
    input_option.on_enter = [&, this] {
        // Reset scroll to bottom on new command
        scroll_offset_ = 0;
        
        // Add prompt + command to output
        ColoredLine cmdLine = getPromptLine();
        cmdLine.push_back(seg(input_content));
        addToOutput(cmdLine);
        
        // Execute command
        auto result = executeCommand(input_content);
        
        if (result.clear_screen) {
            output_buffer_.clear();
        } else {
            addToOutput(result.output);
        }
        
        if (result.should_exit) {
            screen.Exit();
        }
        
        input_content.clear();
        history_index_ = -1;  // Reset history browsing
        saved_input.clear();
    };
    
    auto input_component = Input(&input_content, "", input_option);
    
    // Wrap input component to catch arrow keys and page up/down
    auto wrapped_input = CatchEvent(input_component, [&, this](Event event) {
        // Arrow Up - go back in history
        if (event == Event::ArrowUp) {
            if (!history_.empty()) {
                if (history_index_ == -1) {
                    // Start browsing from the end
                    saved_input = input_content;
                    history_index_ = static_cast<int>(history_.size()) - 1;
                } else if (history_index_ > 0) {
                    history_index_--;
                }
                if (history_index_ >= 0 && history_index_ < static_cast<int>(history_.size())) {
                    input_content = history_[history_index_];
                }
            }
            return true;
        }
        
        // Arrow Down - go forward in history
        if (event == Event::ArrowDown) {
            if (history_index_ != -1) {
                history_index_++;
                if (history_index_ >= static_cast<int>(history_.size())) {
                    // Back to current input
                    history_index_ = -1;
                    input_content = saved_input;
                } else {
                    input_content = history_[history_index_];
                }
            }
            return true;
        }
        
        // Page Up - scroll up
        if (event == Event::PageUp) {
            auto terminal_size = ftxui::Terminal::Size();
            int available_height = terminal_size.dimy - 2;
            int max_scroll = std::max(0, static_cast<int>(output_buffer_.size()) - available_height);
            scroll_offset_ = std::min(scroll_offset_ + 10, max_scroll);
            return true;
        }
        
        // Page Down - scroll down
        if (event == Event::PageDown) {
            scroll_offset_ = std::max(0, scroll_offset_ - 10);
            return true;
        }
        
        // Home - scroll to top
        if (event == Event::Home) {
            auto terminal_size = ftxui::Terminal::Size();
            int available_height = terminal_size.dimy - 2;
            scroll_offset_ = std::max(0, static_cast<int>(output_buffer_.size()) - available_height);
            return true;
        }
        
        // End - scroll to bottom
        if (event == Event::End) {
            scroll_offset_ = 0;
            return true;
        }
        
        return false;  // Let other events pass through
    });
    
    auto renderer = Renderer(wrapped_input, [&, this] {
        Elements output_lines;
        
        // Calculate available height for output (total height minus input line)
        auto terminal_size = ftxui::Terminal::Size();
        int available_height = terminal_size.dimy - 2;
        
        // Calculate which lines to show based on scroll offset
        int total_lines = static_cast<int>(output_buffer_.size());
        int end_idx = total_lines - scroll_offset_;
        int start_idx = std::max(0, end_idx - available_height);
        end_idx = std::min(total_lines, start_idx + available_height);
        
        for (int i = start_idx; i < end_idx; i++) {
            output_lines.push_back(toElement(output_buffer_[i]));
        }
        
        // Fill remaining space with empty lines to push input to bottom
        while (static_cast<int>(output_lines.size()) < available_height) {
            output_lines.push_back(text(""));
        }
        
        // Build prompt element
        Elements prompt_elements;
        auto promptLine = getPromptLine();
        for (const auto& segment : promptLine) {
            auto el = text(segment.text);
            if (segment.color != TermColor::Default) {
                el = el | color(toFtxuiColor(segment.color));
            }
            if (segment.bold) {
                el = el | bold;
            }
            prompt_elements.push_back(el);
        }
        
        // Add scroll indicator if not at bottom
        Element scroll_indicator = text("");
        if (scroll_offset_ > 0) {
            scroll_indicator = text(" [+" + std::to_string(scroll_offset_) + " lines below - PgDn to scroll]") | color(Color::GrayDark);
        }
        
        return vbox({
            vbox(output_lines),
            hbox({
                hbox(prompt_elements),
                wrapped_input->Render(),
                scroll_indicator,
            }),
        });
    });
    
    screen.Loop(renderer);
}

} // namespace hacksim

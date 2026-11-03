#include "../include/htop.hpp"
#include "../include/utils.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <atomic>
#include <algorithm>
#include <mutex>

namespace hacksim {

struct Process {
    int pid;
    std::string user;
    int priority;
    int nice;
    std::string virt;
    std::string res;
    std::string shr;
    char state;
    float cpu;
    float mem;
    std::string time;
    std::string command;
};

static std::vector<Process> generateProcesses() {
    std::vector<Process> procs = {
        {1, "root", 20, 0, "169M", "13M", "8M", 'S', 0.0f, 0.1f, "0:02.34", "/sbin/init"},
        {2, "root", 20, 0, "0", "0", "0", 'S', 0.0f, 0.0f, "0:00.05", "[kthreadd]"},
        {3, "root", 0, -20, "0", "0", "0", 'I', 0.0f, 0.0f, "0:00.00", "[rcu_gp]"},
        {4, "root", 0, -20, "0", "0", "0", 'I', 0.0f, 0.0f, "0:00.00", "[rcu_par_gp]"},
        {9, "root", 20, 0, "0", "0", "0", 'S', 0.0f, 0.0f, "0:00.32", "[ksoftirqd/0]"},
        {10, "root", 20, 0, "0", "0", "0", 'I', 0.0f, 0.0f, "0:01.45", "[rcu_sched]"},
        {11, "root", -100, 0, "0", "0", "0", 'S', 0.0f, 0.0f, "0:00.12", "[migration/0]"},
        {15, "root", 20, 0, "0", "0", "0", 'S', 0.0f, 0.0f, "0:00.00", "[cpuhp/0]"},
        {142, "root", 20, 0, "51M", "8M", "7M", 'S', 0.0f, 0.1f, "0:00.78", "/lib/systemd/systemd-journald"},
        {178, "root", 20, 0, "24M", "6M", "4M", 'S', 0.0f, 0.1f, "0:00.45", "/lib/systemd/systemd-udevd"},
        {312, "systemd+", 20, 0, "16M", "8M", "7M", 'S', 0.0f, 0.1f, "0:00.11", "/lib/systemd/systemd-resolved"},
        {412, "root", 20, 0, "238M", "20M", "12M", 'S', 0.0f, 0.2f, "0:00.87", "/usr/sbin/sshd -D"},
        {486, "root", 20, 0, "347M", "28M", "18M", 'S', 0.3f, 0.3f, "0:05.21", "/usr/sbin/NetworkManager"},
        {502, "root", 20, 0, "8M", "3M", "2M", 'S', 0.0f, 0.0f, "0:00.02", "/usr/sbin/cron -f"},
        {521, "root", 20, 0, "165M", "12M", "8M", 'S', 0.0f, 0.1f, "0:00.45", "/usr/sbin/apache2 -k start"},
        {534, "www-data", 20, 0, "167M", "8M", "4M", 'S', 0.2f, 0.1f, "0:00.12", "/usr/sbin/apache2 -k start"},
        {535, "www-data", 20, 0, "167M", "9M", "4M", 'S', 0.1f, 0.1f, "0:00.18", "/usr/sbin/apache2 -k start"},
        {612, "root", 20, 0, "512M", "45M", "22M", 'S', 0.7f, 0.5f, "0:08.92", "python3 /usr/share/exploitdb/searchsploit"},
        {701, "postgres", 20, 0, "215M", "32M", "28M", 'S', 0.1f, 0.4f, "0:01.33", "/usr/lib/postgresql/15/bin/postgres"},
        {702, "postgres", 20, 0, "215M", "8M", "4M", 'S', 0.0f, 0.1f, "0:00.05", "postgres: checkpointer"},
        {703, "postgres", 20, 0, "215M", "6M", "2M", 'S', 0.0f, 0.1f, "0:00.12", "postgres: background writer"},
        {704, "postgres", 20, 0, "215M", "10M", "6M", 'S', 0.0f, 0.1f, "0:00.08", "postgres: walwriter"},
        {705, "postgres", 20, 0, "216M", "7M", "3M", 'S', 0.0f, 0.1f, "0:00.15", "postgres: autovacuum launcher"},
        {842, "root", 20, 0, "178M", "16M", "10M", 'S', 0.0f, 0.2f, "0:00.08", "/bin/login -f"},
        {901, "root", 20, 0, "892M", "65M", "32M", 'S', 2.3f, 0.8f, "0:15.67", "/usr/bin/msfconsole"},
        {987, "root", 20, 0, "12M", "4M", "3M", 'S', 0.0f, 0.0f, "0:00.01", "/usr/sbin/irqbalance"},
        {1024, "root", 20, 0, "45M", "12M", "8M", 'R', 1.2f, 0.1f, "0:00.34", "htop"},
        {1102, "root", 20, 0, "124M", "18M", "12M", 'S', 0.0f, 0.2f, "0:02.11", "/usr/sbin/rsyslogd"},
        {1205, "root", 20, 0, "78M", "8M", "4M", 'S', 0.0f, 0.1f, "0:00.56", "/usr/sbin/cron -f"},
        {1312, "root", 20, 0, "256M", "34M", "18M", 'S', 0.4f, 0.4f, "0:03.78", "/usr/bin/python3 /opt/burpsuite"},
        {1456, "root", 20, 0, "98M", "14M", "8M", 'S', 0.0f, 0.1f, "0:01.23", "/usr/sbin/dnsmasq"},
        {1523, "root", 20, 0, "324M", "48M", "24M", 'S', 1.5f, 0.6f, "0:12.45", "/usr/bin/nmap -sV 192.168.1.0/24"},
        {1678, "root", 20, 0, "156M", "22M", "14M", 'S', 0.8f, 0.3f, "0:04.32", "/usr/bin/hydra -L users.txt"},
        {1701, "root", 20, 0, "89M", "16M", "10M", 'S', 0.3f, 0.2f, "0:02.11", "/usr/bin/john --wordlist=/usr/share/wordlists"},
        {1789, "mysql", 20, 0, "1.2G", "128M", "64M", 'S', 0.5f, 1.6f, "0:08.76", "/usr/sbin/mysqld"},
        {1856, "root", 20, 0, "234M", "28M", "16M", 'S', 0.2f, 0.3f, "0:01.89", "/usr/bin/aircrack-ng capture.cap"},
        {1923, "root", 20, 0, "445M", "52M", "28M", 'S', 1.1f, 0.6f, "0:06.54", "/usr/bin/wireshark"},
        {2001, "root", 20, 0, "67M", "12M", "8M", 'S', 0.0f, 0.1f, "0:00.34", "/usr/sbin/bluetoothd"},
        {2034, "root", 20, 0, "189M", "24M", "16M", 'S', 0.1f, 0.3f, "0:01.23", "/usr/lib/xorg/Xorg"},
        {2156, "root", 20, 0, "78M", "10M", "6M", 'S', 0.0f, 0.1f, "0:00.45", "bash"},
        {2201, "root", 20, 0, "512M", "64M", "32M", 'S', 3.2f, 0.8f, "0:18.92", "/usr/bin/sqlmap -u http://target"},
        {2289, "root", 20, 0, "34M", "6M", "4M", 'S', 0.0f, 0.1f, "0:00.12", "tmux: server"},
        {2345, "root", 20, 0, "78M", "10M", "6M", 'S', 0.0f, 0.1f, "0:00.23", "bash"},
        {2401, "root", 20, 0, "156M", "18M", "12M", 'S', 0.6f, 0.2f, "0:02.67", "/usr/bin/nikto -h target.com"},
        {2512, "nobody", 20, 0, "12M", "4M", "2M", 'S', 0.0f, 0.0f, "0:00.08", "/usr/sbin/dnsmasq"},
        {2589, "root", 20, 0, "267M", "32M", "18M", 'S', 0.4f, 0.4f, "0:03.45", "/usr/bin/gobuster dir -u http://target"},
        {2678, "root", 20, 0, "98M", "14M", "8M", 'S', 0.2f, 0.2f, "0:01.12", "/usr/bin/dirb http://target"},
        {2756, "root", 20, 0, "456M", "56M", "28M", 'S', 2.8f, 0.7f, "0:14.32", "/usr/bin/hashcat -m 0 hashes.txt"},
        {2834, "root", 20, 0, "23M", "5M", "3M", 'S', 0.0f, 0.1f, "0:00.23", "nc -lvp 4444"},
        {2901, "root", 20, 0, "89M", "12M", "8M", 'S', 0.1f, 0.1f, "0:00.89", "/usr/bin/ettercap -T -i eth0"},
    };
    
    // Randomize CPU/MEM slightly on init
    for (auto& p : procs) {
        p.cpu += (randomInt(-10, 10) / 10.0f);
        if (p.cpu < 0) p.cpu = 0;
        p.mem += (randomInt(-5, 5) / 100.0f);
        if (p.mem < 0) p.mem = 0;
    }
    
    return procs;
}

void run_htop(std::function<bool()> /*should_exit*/) {
    using namespace ftxui;
    
    auto screen = ScreenInteractive::Fullscreen();
    
    std::atomic<bool> running{true};
    std::vector<Process> processes = generateProcesses();
    std::mutex proc_mutex;
    
    // CPU usage per core (current value)
    float cpu_usage[8] = {0};
    for (int i = 0; i < 8; i++) {
        cpu_usage[i] = randomInt(5, 60) / 1.0f;
    }
    
    int mem_used = randomInt(2000, 4000);
    int mem_total = 8192;
    int swap_used = randomInt(0, 500);
    int swap_total = 2048;
    int uptime_secs = randomInt(3600, 360000);
    float load[3] = {
        randomInt(50, 200) / 100.0f,
        randomInt(40, 180) / 100.0f,
        randomInt(30, 150) / 100.0f
    };
    
    int scroll_offset = 0;
    int selected_row = 0;
    
    // Animation thread
    std::thread updater([&]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            
            {
                std::lock_guard<std::mutex> lock(proc_mutex);
                
                // Update CPU usage (current values)
                for (int i = 0; i < 8; i++) {
                    float delta = randomInt(-15, 15) / 1.0f;
                    cpu_usage[i] += delta;
                    if (cpu_usage[i] < 2) cpu_usage[i] = 2 + randomInt(0, 10);
                    if (cpu_usage[i] > 98) cpu_usage[i] = 98 - randomInt(0, 10);
                }
                
                // Update process stats - more dynamic changes
                for (auto& p : processes) {
                    // Random CPU fluctuation
                    float cpu_delta = randomInt(-30, 30) / 10.0f;
                    p.cpu += cpu_delta;
                    
                    // Occasionally spike a random process
                    if (randomInt(0, 100) < 5) {
                        p.cpu += randomInt(10, 40);
                    }
                    
                    // Clamp
                    if (p.cpu < 0) p.cpu = randomInt(0, 5) / 10.0f;
                    if (p.cpu > 100) p.cpu = 95.0f + randomInt(0, 50) / 10.0f;
                    
                    // Memory changes less frequently
                    if (randomInt(0, 100) < 20) {
                        p.mem += randomInt(-10, 10) / 100.0f;
                        if (p.mem < 0) p.mem = 0.1f;
                        if (p.mem > 10) p.mem = 10.0f;
                    }
                    
                    // Occasionally change state
                    if (randomInt(0, 100) < 3) {
                        p.state = (p.state == 'S') ? 'R' : 'S';
                    }
                }
                
                // Sort by CPU usage (descending)
                std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
                    return a.cpu > b.cpu;
                });
            }
            
            // Update system stats
            mem_used += randomInt(-100, 100);
            if (mem_used < 1500) mem_used = 1500;
            if (mem_used > 7000) mem_used = 7000;
            
            uptime_secs++;
            
            // Load average changes slowly
            load[0] += (randomInt(-5, 5) / 100.0f);
            if (load[0] < 0.1f) load[0] = 0.1f;
            if (load[0] > 4.0f) load[0] = 4.0f;
            
            load[1] += (randomInt(-3, 3) / 100.0f);
            if (load[1] < 0.1f) load[1] = 0.1f;
            
            load[2] += (randomInt(-2, 2) / 100.0f);
            if (load[2] < 0.1f) load[2] = 0.1f;
            
            screen.PostEvent(Event::Custom);
        }
    });
    
    auto component = CatchEvent(Renderer([&] {
        std::lock_guard<std::mutex> lock(proc_mutex);
        
        auto term_size = Terminal::Size();
        int width = term_size.dimx;
        int height = term_size.dimy;
        
        // CPU bars - show actual usage
        Elements cpu_bars;
        int num_cpus = std::min(8, std::max(2, (height - 14) / 2 + 4));  // At least 2, scale with height
        
        for (int i = 0; i < num_cpus; i++) {
            float usage = cpu_usage[i];
            float progress = usage / 100.0f;
            
            std::stringstream usage_str;
            usage_str << std::fixed << std::setprecision(1) << std::setw(5) << usage << "%";
            
            // Color based on usage
            Color bar_color = Color::Green;
            if (usage > 70) bar_color = Color::Red;
            else if (usage > 40) bar_color = Color::Yellow;
            
            auto bar = hbox({
                text(std::to_string(i + 1)) | size(WIDTH, EQUAL, 2) | color(Color::Cyan),
                text(" [") | color(Color::White),
                gauge(progress) | flex | color(bar_color),
                text("]") | color(Color::White),
                text(usage_str.str()) | size(WIDTH, EQUAL, 7) | color(bar_color),
            });
            cpu_bars.push_back(bar);
        }
        
        // Memory bar
        float mem_progress = static_cast<float>(mem_used) / mem_total;
        std::stringstream mem_str;
        mem_str << std::setw(4) << mem_used << "M/" << mem_total << "M";
        
        auto mem_bar = hbox({
            text("Mem") | size(WIDTH, EQUAL, 4) | color(Color::Cyan),
            text("[") | color(Color::White),
            gauge(mem_progress) | flex | color(mem_progress > 0.8 ? Color::Red : Color::Green),
            text("]") | color(Color::White),
            text(mem_str.str()) | size(WIDTH, EQUAL, 14),
        });
        
        // Swap bar
        float swap_progress = static_cast<float>(swap_used) / swap_total;
        std::stringstream swap_str;
        swap_str << std::setw(4) << swap_used << "M/" << swap_total << "M";
        
        auto swap_bar = hbox({
            text("Swp") | size(WIDTH, EQUAL, 4) | color(Color::Cyan),
            text("[") | color(Color::White),
            gauge(swap_progress) | flex | color(swap_progress > 0.5 ? Color::Yellow : Color::Cyan),
            text("]") | color(Color::White),
            text(swap_str.str()) | size(WIDTH, EQUAL, 14),
        });
        
        // Count running tasks
        int tasks_running = 0;
        for (const auto& p : processes) {
            if (p.state == 'R') tasks_running++;
        }
        
        // Stats line
        int hours = uptime_secs / 3600;
        int mins = (uptime_secs % 3600) / 60;
        std::stringstream stats;
        stats << "Tasks: " << processes.size() << ", " << tasks_running << " running; ";
        stats << "Load average: " << std::fixed << std::setprecision(2) << load[0] << " " << load[1] << " " << load[2] << "; ";
        stats << "Uptime: " << hours << ":" << std::setfill('0') << std::setw(2) << mins;
        
        // Process header
        auto proc_header = hbox({
            text("  PID") | size(WIDTH, EQUAL, 7) | color(Color::Black) | bgcolor(Color::Green),
            text("USER    ") | size(WIDTH, EQUAL, 9) | color(Color::Black) | bgcolor(Color::Green),
            text(" PRI") | size(WIDTH, EQUAL, 5) | color(Color::Black) | bgcolor(Color::Green),
            text("  NI") | size(WIDTH, EQUAL, 5) | color(Color::Black) | bgcolor(Color::Green),
            text("  VIRT") | size(WIDTH, EQUAL, 7) | color(Color::Black) | bgcolor(Color::Green),
            text("   RES") | size(WIDTH, EQUAL, 7) | color(Color::Black) | bgcolor(Color::Green),
            text("   SHR") | size(WIDTH, EQUAL, 7) | color(Color::Black) | bgcolor(Color::Green),
            text(" S") | size(WIDTH, EQUAL, 3) | color(Color::Black) | bgcolor(Color::Green),
            text(" CPU%") | size(WIDTH, EQUAL, 6) | color(Color::Black) | bgcolor(Color::Green),
            text(" MEM%") | size(WIDTH, EQUAL, 6) | color(Color::Black) | bgcolor(Color::Green),
            text("   TIME+") | size(WIDTH, EQUAL, 10) | color(Color::Black) | bgcolor(Color::Green),
            text(" Command") | flex | color(Color::Black) | bgcolor(Color::Green),
        });
        
        // Calculate visible processes based on window height
        // Header area: CPU bars + mem + swap + stats + separator + proc_header + separator + footer = variable
        int header_lines = num_cpus + 5;  // cpu bars + mem + swap + stats + sep
        int footer_lines = 2;  // sep + footer
        int visible_procs = std::max(5, height - header_lines - footer_lines - 1);
        
        // Adjust scroll if needed
        if (scroll_offset > static_cast<int>(processes.size()) - visible_procs) {
            scroll_offset = std::max(0, static_cast<int>(processes.size()) - visible_procs);
        }
        
        // Process list
        Elements proc_lines;
        for (int i = scroll_offset; i < std::min(scroll_offset + visible_procs, static_cast<int>(processes.size())); i++) {
            const auto& p = processes[i];
            std::stringstream pid_ss, pri_ss, ni_ss, cpu_ss, mem_ss;
            pid_ss << std::setw(5) << p.pid;
            pri_ss << std::setw(3) << p.priority;
            ni_ss << std::setw(3) << p.nice;
            cpu_ss << std::fixed << std::setprecision(1) << std::setw(5) << p.cpu;
            mem_ss << std::fixed << std::setprecision(1) << std::setw(5) << p.mem;
            
            Color row_color = Color::Default;
            if (p.state == 'R') row_color = Color::Green;
            
            Color cpu_color = Color::Default;
            if (p.cpu > 50) cpu_color = Color::Red;
            else if (p.cpu > 20) cpu_color = Color::Yellow;
            else if (p.cpu > 5) cpu_color = Color::Green;
            
            // Highlight selected row
            bool is_selected = (i == scroll_offset + selected_row);
            
            auto proc_line = hbox({
                text(pid_ss.str()) | size(WIDTH, EQUAL, 7) | color(Color::Cyan),
                text(p.user) | size(WIDTH, EQUAL, 9) | color(Color::Yellow),
                text(pri_ss.str()) | size(WIDTH, EQUAL, 5),
                text(ni_ss.str()) | size(WIDTH, EQUAL, 5),
                text(p.virt) | size(WIDTH, EQUAL, 7) | color(Color::Green),
                text(p.res) | size(WIDTH, EQUAL, 7) | color(Color::Cyan),
                text(p.shr) | size(WIDTH, EQUAL, 7),
                text(std::string(1, p.state)) | size(WIDTH, EQUAL, 3) | color(row_color),
                text(cpu_ss.str()) | size(WIDTH, EQUAL, 6) | color(cpu_color),
                text(mem_ss.str()) | size(WIDTH, EQUAL, 6),
                text(p.time) | size(WIDTH, EQUAL, 10),
                text(p.command) | flex | color(row_color),
            });
            
            if (is_selected) {
                proc_line = proc_line | bgcolor(Color::GrayDark);
            }
            
            proc_lines.push_back(proc_line);
        }
        
        // Fill remaining space if not enough processes
        while (static_cast<int>(proc_lines.size()) < visible_procs) {
            proc_lines.push_back(text(""));
        }
        
        // Footer
        auto footer = hbox({
            text(" F1") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Help ") | color(Color::White),
            text(" F2") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Setup ") | color(Color::White),
            text(" F3") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Search ") | color(Color::White),
            text(" F4") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Filter ") | color(Color::White),
            text(" F5") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Tree ") | color(Color::White),
            text(" F6") | color(Color::Black) | bgcolor(Color::Cyan),
            text("SortBy ") | color(Color::White),
            text(" F9") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Kill ") | color(Color::White),
            text(" F10") | color(Color::Black) | bgcolor(Color::Cyan),
            text("Quit ") | color(Color::White),
            text(" q") | color(Color::Black) | bgcolor(Color::Yellow),
            text("=Exit") | color(Color::White),
            filler(),
            text("Sorted by CPU%") | color(Color::GrayDark),
        });
        
        return vbox({
            vbox(cpu_bars),
            mem_bar,
            swap_bar,
            text(stats.str()) | color(Color::White),
            separator(),
            proc_header,
            vbox(proc_lines) | flex,
            separator(),
            footer,
        });
    }), [&](Event event) {
        if (event == Event::Character('q') || event == Event::Escape || event == Event::F10) {
            running = false;
            screen.Exit();
            return true;
        }
        if (event == Event::ArrowDown) {
            auto term_size = Terminal::Size();
            int visible = std::max(5, term_size.dimy - 15);
            if (selected_row < visible - 1) {
                selected_row++;
            } else if (scroll_offset < static_cast<int>(processes.size()) - visible) {
                scroll_offset++;
            }
            return true;
        }
        if (event == Event::ArrowUp) {
            if (selected_row > 0) {
                selected_row--;
            } else if (scroll_offset > 0) {
                scroll_offset--;
            }
            return true;
        }
        if (event == Event::PageDown) {
            auto term_size = Terminal::Size();
            int visible = std::max(5, term_size.dimy - 15);
            scroll_offset = std::min(scroll_offset + visible, std::max(0, static_cast<int>(processes.size()) - visible));
            return true;
        }
        if (event == Event::PageUp) {
            auto term_size = Terminal::Size();
            int visible = std::max(5, term_size.dimy - 15);
            scroll_offset = std::max(0, scroll_offset - visible);
            return true;
        }
        return false;
    });
    
    screen.Loop(component);
    running = false;
    updater.join();
}

} // namespace hacksim

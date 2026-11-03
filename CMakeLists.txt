cmake_minimum_required(VERSION 3.14)
project(hacksim 
    VERSION 1.0.0
    DESCRIPTION "Realistic hacker terminal simulator (Kali/Mr. Robot style)"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch FTXUI
include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# Main executable
add_executable(hacksim
    src/main.cpp
    src/terminal.cpp
    src/commands.cpp
    src/filesystem.cpp
    src/nmap.cpp
    src/tools.cpp
    src/htop.cpp
    src/utils.cpp
)

target_include_directories(hacksim PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(hacksim
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

# Install
install(TARGETS hacksim DESTINATION bin)

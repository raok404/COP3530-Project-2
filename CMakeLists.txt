cmake_minimum_required(VERSION 4.1)
project(COP3530_Project_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(json)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
cmake_minimum_required(VERSION 3.15)
project(UrbanTrafficSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    GIT_SHALLOW    TRUE  
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE 
)
FetchContent_MakeAvailable(nlohmann_json)


FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.9
    GIT_SHALLOW    TRUE
)

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG        2.6
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(imgui imgui-sfml)








include_directories(src)


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML

)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:sfml-system>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
cmake_minimum_required(VERSION 3.10)
project(GEO_WAR)

set(CMAKE_CXX_STANDARD 17)

# Set SFML root directory
set(SFML_ROOT "/opt/homebrew/include/SFML")

# Set CMake module path to find SFMLConfig.cmake
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${SFML_ROOT}/cmake/Modules")

include_directories(include)

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
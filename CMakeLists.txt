cmake_minimum_required(VERSION 3.10)

project(SFML_SIMULATION)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(SFML_SIMULATION ${SOURCES})
target_link_libraries(SFML_SIMULATION sfml-graphics sfml-window sfml-system)

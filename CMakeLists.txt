cmake_minimum_required(VERSION 3.10.0)
project(decisionTrees)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "main.cpp")
add_executable(decisionTrees ${SOURCES})

add_custom_target(run
    COMMAND decisionTrees
    DEPENDS decisionTrees
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

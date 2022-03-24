cmake_minimum_required(VERSION 3.1)

project(philo)

#-----Google Test Definitions-----#

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)

#-----Source File Definitions-----#

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pthread -g")

file(GLOB sources 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/input/*.c"
        )

add_executable(philo ${sources})
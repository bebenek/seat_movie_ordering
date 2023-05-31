cmake_minimum_required(VERSION 3.10)
project(async_tcp_echo_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(conan_toolchain.cmake)

# conan_basic_setup()

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/session.cpp src/server.cpp)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} Threads::Threads)

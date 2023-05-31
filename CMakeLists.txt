cmake_minimum_required(VERSION 3.10)
project(async_tcp_echo_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(conan_toolchain.cmake)

# conan_basic_setup()

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/session.cpp src/server.cpp src/request_handler.cpp src/database.cpp)
find_package(Threads REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and 
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs 
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF) 
find_package(Boost 1.71.0 COMPONENTS system REQUIRED)
find_package(RapidJSON REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} Threads::Threads ${Boost_LIBRARIES} RapidJSON)

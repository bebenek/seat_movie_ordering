cmake_minimum_required(VERSION 3.10)
project(movie_reservation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(conan_toolchain.cmake)

# conan_basic_setup()

include_directories(include)

find_package(Threads REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and 
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs 
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF) 

find_package(Boost 1.71.0 COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
find_package(RapidJSON REQUIRED)
include_directories(${Rapidjson_INCLUDE_DIRS})
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(handlers src/request_handler.cpp src/service.cpp src/database.cpp src/response_generator.cpp src/file_parser.cpp)

add_executable(${PROJECT_NAME} src/main.cpp src/session.cpp src/server.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE handlers ${CONAN_LIBS} Threads::Threads ${Boost_LIBRARIES} )

add_executable(cpp_test tests/request_handler_test.cpp tests/service_test.cpp tests/database_test.cpp tests/response_generator_test.cpp)
target_link_libraries(cpp_test PRIVATE handlers GTest::gtest_main ${CONAN_LIBS} Threads::Threads ${GTEST_LIBRARIES} )

enable_testing()

include(GoogleTest)
gtest_discover_tests(cpp_test)
# add_test(NAME    cpp_test 
#          COMMAND sample_test_case)

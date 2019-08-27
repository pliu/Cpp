cmake_minimum_required(VERSION 3.6)
project(Cpp)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DINSTRUMENT)

file(GLOB HASH_TABLES
        "Miscellaneous/HashTables/*ht.h"
        "Miscellaneous/HashTables/*ht.cpp"
        "Miscellaneous/HashTables/murmur3_hash.*")
file(GLOB UTILS
        "Miscellaneous/Utils/*.h"
        "Miscellaneous/Utils/*.cpp")

add_executable(jump_hash_test Miscellaneous/jump_hash_test.cpp)
add_executable(circular_file_io_test Miscellaneous/circular_file_io_test.cpp)
add_executable(ht_perf_test Miscellaneous/ht_perf_test.cpp ${HASH_TABLES} ${UTILS})
add_executable(event_test Miscellaneous/event_test.cpp)
add_executable(016 LeetCode/016.cpp)

if(WIN32)
    target_link_libraries(event_test ws2_32 event)
else()
    target_link_libraries(event_test event)
endif(WIN32)

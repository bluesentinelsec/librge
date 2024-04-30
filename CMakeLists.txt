cmake_minimum_required(VERSION 3.14)
project(librge VERSION 1.0 DESCRIPTION "librge library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

#--------------------------
#   Source files
#--------------------------
set(SOURCE_FILES
        src/systems.cpp
)

set(HEADER_FILES
        include/librge/rge.h
)

add_subdirectory(external/physfs-release-3.2.0)
add_subdirectory(external/raylib-5.0)

add_library(rge_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(rge_shared SHARED ${SOURCE_FILES} ${HEADER_FILES})

#--------------------------
#   Header includes
#--------------------------
target_include_directories(rge_static PRIVATE
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/physfs-release-3.2.0/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.0/src
)

target_include_directories(rge_shared PRIVATE
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/physfs-release-3.2.0/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external/raylib-5.0/src
)


#--------------------------
#   Link libraries
#--------------------------
target_link_libraries(rge_shared PRIVATE physfs-static raylib_static)
target_link_libraries(rge_static PRIVATE physfs-static raylib_static)

set_target_properties(rge_shared PROPERTIES OUTPUT_NAME "rge")
set_target_properties(rge_static PROPERTIES OUTPUT_NAME "rge")


install(TARGETS rge_shared rge_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include/ DESTINATION include)


#--------------------------
#   Unit tests
#--------------------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        test_main
        tests/test_main.cpp
)
target_link_libraries(
        test_main
        PRIVATE
        GTest::gtest_main
        rge_static
)
target_include_directories(test_main PUBLIC
        include
)
include(GoogleTest)
gtest_discover_tests(test_main)


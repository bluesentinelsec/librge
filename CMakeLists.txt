cmake_minimum_required(VERSION 3.14)
project(librge VERSION 1.0 DESCRIPTION "librge library")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


#--------------------------
#   Source and header files
#--------------------------
set(SOURCE_FILES
        src/engine.cpp
        src/fileio.cpp
        src/media.cpp
        src/camera2D.cpp
        src/keyboard.cpp
)

set(HEADER_FILES
        include/librge/rge.h
        include/librge/logger.h
)


#--------------------------
#   Add external projects and
#   define build outputs
#--------------------------
add_subdirectory(external/physfs-release-3.2.0)
add_subdirectory(external/raylib-5.0)

add_library(rge_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(rge_shared SHARED ${SOURCE_FILES} ${HEADER_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(rge_shared PRIVATE NDEBUG)
    target_compile_definitions(rge_static PRIVATE NDEBUG)
endif()

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


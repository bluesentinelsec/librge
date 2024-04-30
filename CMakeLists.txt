cmake_minimum_required(VERSION 3.0)
project(librge VERSION 1.0 DESCRIPTION "librge library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(SOURCE_FILES
        src/systems.cpp

)

set(HEADER_FILES
        include/librge/rge.h
)

add_library(librge_static STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(librge_shared SHARED ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(librge_static PRIVATE include)
target_include_directories(librge_shared PRIVATE include)

set_target_properties(librge_shared PROPERTIES OUTPUT_NAME "librge")
set_target_properties(librge_static PROPERTIES OUTPUT_NAME "librge")

if (MSVC)
    # static link the C++ runtime library: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
    set_target_properties(librge_shared PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set_target_properties(librge_static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else ()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif ()


install(TARGETS librge_shared librge_static
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
        GTest::gtest_main
        librge_static
)
target_include_directories(test_main PUBLIC include)
include(GoogleTest)
gtest_discover_tests(test_main)


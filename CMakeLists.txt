cmake_minimum_required(VERSION 3.5)

project(fft)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")
endif()

# scripts
include(dep/cotire/CMake/cotire.cmake)
include(dep/jet-live/cmake/jet_live_setup.cmake)
set(JET_LIVE_BUILD_EXAMPLE OFF)

# module paths

# packages
find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML REQUIRED system window graphics)


# subdirectories
add_subdirectory(src)
add_subdirectory(dep/jet-live)

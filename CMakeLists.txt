cmake_minimum_required(VERSION 3.5)

project(fft)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)

# Check optional dependencies
if(EXISTS dep/cotire)
set(ENABLE_COTIRE)
endif()
if(EXISTS dep/jet-live)
set(ENABLE_JET_LIVE)
endif()

# Windows related stuff
if (MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")
endif()

# scripts
if(ENABLE_COTIRE)
include(dep/cotire/CMake/cotire.cmake)
endif()
if(ENABLE_JET_LIVE)
include(dep/jet-live/cmake/jet_live_setup.cmake)
set(JET_LIVE_BUILD_EXAMPLE OFF)
endif()

# module paths
set(SFML_DIR "${SFML_PATH}/lib/cmake/SFML")

# packages
if(UNIX)
find_package(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
endif()
find_package(SFML COMPONENTS system window graphics REQUIRED)


# subdirectories
add_subdirectory(src)
if(ENABLE_JET_LIVE)
#add_subdirectory(dep/jet-live)
endif()

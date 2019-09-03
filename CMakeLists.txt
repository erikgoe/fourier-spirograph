cmake_minimum_required(VERSION 3.5)

project(fft)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)

# VCPKG
if( VCPKG_SOURCE_DIR )
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

# Windows related stuff
if (MSVC)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MTd")
set(SFML_STATIC_LIBRARIES TRUE)
endif()

# scripts
#include(dep/cotire/CMake/cotire.cmake)
#include(dep/jet-live/cmake/jet_live_setup.cmake)
set(JET_LIVE_BUILD_EXAMPLE OFF)

# module paths
set(SFML_DIR "${VCPKG_SOURCE_DIR}/installed/x86-windows-static/share/sfml")
set(FREETYPE_LIBRARY "${VCPKG_SOURCE_DIR}/installed/x86-windows-static/lib/freetype")
set(FREETYPE_INCLUDE_DIRS "${VCPKG_SOURCE_DIR}/installed/x86-windows-static/include/freetype")

# packages
#find_package(PkgConfig REQUIRED)
#PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)


# subdirectories
add_subdirectory(src)
#add_subdirectory(dep/jet-live)

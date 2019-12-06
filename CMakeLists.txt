cmake_minimum_required(VERSION 2.6)
project(xal/lv2-plugins)

IF(DEFINED ENV{LV2_INSTALL_DIR} AND DEFINED ENV{LV2_INSTALL_DIR})
        message("INSTALL DIR set")
        set(LV2_INSTALL_DIR $ENV{LV2_INSTALL_DIR} CACHE PATH "Specifies where the LV2 libraries should be installed")
ELSE()
        message("INSTALL DIR not set")
        set(LV2_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/plugins) # CACHE PATH "Specifies where the LV2 libraries should be installed")
ENDIF()
add_definitions(-Wall)

set(CMAKE_INSTALL_PREFIX "")
# Check for various libraries:
find_package(PkgConfig REQUIRED)
include(FindPkgConfig)
pkg_check_modules(LV2
                REQUIRED
                lv2)
if(LV2_FOUND)
        message(STATUS "Found LV2")
else()
        message(STATUS "Didn't find LV2")
endif()

include_directories(${LV2_INCLUDE_DIRS})
link_libraries(${LV2_LIBRARY_DIRS})

message(STATUS "LV2_INSTALL_DIR:  ${LV2_INSTALL_DIR}")
message(STATUS "LV2_INCLUDE_DIRS: ${LV2_INCLUDE_DIRS}")
message(STATUS "LV2_LIBRARY_DIRS: ${LV2_LIBRARY_DIR}")
message(STATUS "LV2_LIBRARIES: ${LV2_LIBRARIES}")

if(APPLE)
        set(LIB_EXT "dylib")
else()
        set(LIB_EXT "so")
endif()

# Functions needed to build and install plugins
include(${PROJECT_SOURCE_DIR}/build_support/add_plugin.cmake)
# List of plugins:
add_plugin(simple_delay)
add_plugin(lowpass)
# END of list of plugins

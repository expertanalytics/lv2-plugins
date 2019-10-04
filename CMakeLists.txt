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


# Check for various libraries:
find_package(PkgConfig)
pkg_check_modules(LV2 lv2)

include_directories(${LV2_INCLUDE_DIRS})
link_libraries(${LV2_LIBRARY_DIRS})

message(STATUS "LV2_INSTALL_DIR:  ${LV2_INSTALL_DIR}")
message(STATUS "LV2_INCLUDE_DIRS: ${LV2_INCLUDE_DIRS}")
message(STATUS "LV2_LIBRARY_DIRS: ${LV2_LIBRARY_DIR}")
# Add subdirectories:
add_subdirectory(simple_delay)

cmake_minimum_required(VERSION 2.6)
project(xal/lv2-plugins)

if (DEFINED $ENV{LV2_INSTALL_DIR})
        set(LV2_INSTALL_DIR $ENV{LV2_INSTALL_DIR} CACHE PATH "Specifies where the LV2 libraries should be installed")
else()
        set(LV2_INSTALL_DIR /usr/local/lib/lv2 CACHE PATH "Specifies where the LV2 libraries should be installed")
endif()
add_definitions(-Wall)


# Check for various libraries:
find_package(PkgConfig)
pkg_check_modules(LV2 lv2)

include_directories(${LV2_INCLUDE_DIRS})
link_libraries(${LV2_LIBRARY_DIRS})
message(STATUS "LV2_INCLUDE_DIRS: ${LV2_INCLUDE_DIRS}")
message(STATUS "LV2_LIBRARY_DIRS: ${LV2_LIBRARY_DIR}")

# Add subdirectories:
add_subdirectory(simple_delay)

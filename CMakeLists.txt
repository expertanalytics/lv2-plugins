cmake_minimum_required(VERSION 2.6)
project(xal/lv2-plugins)


set(LV2_INSTALL_DIR lib/lv2 CACHE PATH "Specifies where the LV2 libraries should be installed")
add_definitions(-Wall)


# Check for various libraries:
find_package(PkgConfig)
pkg_check_modules(LV2 REQUIRED lv2>=.0.1.0)

include_directories(${LV2_INCLUDE_DIRS})
link_libraries(${LV2_LIBRARY_DIRS})


# Add subdirectories:
add_subdirectory(simple_delay)

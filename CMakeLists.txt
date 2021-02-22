cmake_minimum_required(VERSION 3.4)

project(
    resource-manager
    VERSION 0.1.0
    LANGUAGES CXX
)

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(utils/http-client)

if (BUILD_UNIT_TESTS)
    find_package(GTest REQUIRED)
    pkg_check_modules(GMock REQUIRED "gmock")
    enable_testing()
    add_subdirectory(unit-test)
endif()

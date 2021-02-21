pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(LIBCURL REQUIRED libcurl)

# Boost
find_package(
        Boost 1.58.0
        COMPONENTS program_options
        REQUIRED
)

set(Boost_LIBRARIES Boost::program_options)

add_executable(http_client "${CMAKE_CURRENT_LIST_DIR}/main.cpp")

target_link_libraries(
        http_client
        PRIVATE
        curl
        curlpp
        ${Boost_LIBRARIES}
)

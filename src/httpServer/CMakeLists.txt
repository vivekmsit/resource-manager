pkg_check_modules(CURLPP REQUIRED libhttpserver)

add_library(http_server STATIC src/HttpServer.cpp)

target_include_directories(
        http_server
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/interfaces"
        )

target_link_libraries(
        http_server
        PRIVATE
        httpserver
        resource_manager
)
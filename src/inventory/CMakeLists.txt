add_library(inventory STATIC src/Inventory.cpp)

target_include_directories(
        inventory
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/interfaces"
)

target_link_libraries(
        inventory
        PRIVATE
        curlpp
)
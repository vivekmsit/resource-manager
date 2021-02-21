add_library(resource_manager STATIC src/ResourceManager.cpp)

target_include_directories(
        resource_manager
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/interfaces"
)

target_link_libraries(
        resource_manager
        PRIVATE
        inventory
)
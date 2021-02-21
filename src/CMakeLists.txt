set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(inventory)
add_subdirectory(resourceManager)
add_subdirectory(httpServer)

add_executable(${TARGET_NAME} "${CMAKE_CURRENT_LIST_DIR}/main.cpp")

target_link_libraries(
		${TARGET_NAME}
		PRIVATE
		http_server
		inventory
		resource_manager
)

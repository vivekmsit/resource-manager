set(TARGET_NAME runAllTests)

file(GLOB TEST_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

add_executable(${TARGET_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
        GTest::GTest
        GTest::Main
        ${GMock_LIBRARIES}
        inventory
)

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
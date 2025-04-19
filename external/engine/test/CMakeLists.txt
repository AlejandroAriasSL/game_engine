add_executable(service_locator_test service_locator_test.cpp)

target_link_libraries(service_locator_test
        PRIVATE
        game
        gmock
        gtest_main
        gtest
)
include(GoogleTest)
gtest_discover_tests(service_locator_test)
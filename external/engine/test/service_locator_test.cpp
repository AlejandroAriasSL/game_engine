#include <gtest/gtest.h>
#include <example_engine/service_locator.h>
#include "mocks/mock_window.h"

class ServiceLocatorTestFixture : public ::testing::Test { 
protected:

  Window* mockWindow;  
  
  void SetUp() override {
    ServiceLocator::ShutdownServices();
  }

  void TearDown() override {
    ServiceLocator::ShutdownServices();
  }
};

TEST_F(ServiceLocatorTestFixture, should_initialize_as_nullptr) {

    EXPECT_EQ(ServiceLocator::GetWindow(), nullptr);
}
TEST_F(ServiceLocatorTestFixture, should_assing_window_pointer) {

    EXPECT_EQ(ServiceLocator::GetWindow(), nullptr);

    mockWindow = new MockWindow();
    ServiceLocator::Provide(mockWindow);

    EXPECT_NE(ServiceLocator::GetWindow(), nullptr);
    EXPECT_TRUE(dynamic_cast<MockWindow*>(ServiceLocator::GetWindow().get()));

}
TEST_F(ServiceLocatorTestFixture, should_assing_a_window_pointer_just_once) {

    EXPECT_EQ(ServiceLocator::GetWindow(), nullptr);

    mockWindow = new MockWindow();
    ServiceLocator::Provide(mockWindow);

    EXPECT_NE(ServiceLocator::GetWindow(), nullptr);

    auto* mockWindow2 = new MockWindow();
    ServiceLocator::Provide(mockWindow2);

    EXPECT_EQ(ServiceLocator::GetWindow().get(), mockWindow);

    delete mockWindow2;
}
TEST_F(ServiceLocatorTestFixture, should_shutdown_and_reset_to_nullptr) {

    EXPECT_EQ(ServiceLocator::GetWindow(), nullptr);

    mockWindow = new MockWindow();
    ServiceLocator::Provide(mockWindow);

    EXPECT_NE(ServiceLocator::GetWindow(), nullptr);

    ServiceLocator::ShutdownServices();

    EXPECT_EQ(ServiceLocator::GetWindow(), nullptr);
}
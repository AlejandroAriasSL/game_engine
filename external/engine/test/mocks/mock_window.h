#pragma once
#include <gmock/gmock.h>
#include <example_engine/platform/window.h>

class MockWindow : public Window {
public:
  MOCK_METHOD(void, OpenWindow, (WindowData data), (override));
  MOCK_METHOD(bool, Update, (), (override));
};
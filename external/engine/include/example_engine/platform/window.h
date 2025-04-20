#pragma once
#include <string>
#include <cstdint>

namespace ONI {
struct WindowData {
  std::string title;
  uint32_t width, height;
};

class Window {
public:
    virtual void OpenWindow(WindowData data) = 0;
    virtual bool Update() = 0;
};
}
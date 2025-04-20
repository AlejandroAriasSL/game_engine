#pragma once
#define GLFW_INCLUDE_VULKAN

#include <example_engine/platform/window.h>
#include <GLFW/glfw3.h>
namespace ONI {
class MultiPlatformWindow : public Window {
private:
    GLFWwindow* _window;
public:
    MultiPlatformWindow();
    void OpenWindow(WindowData data) override;
    bool Update() override;
};
}
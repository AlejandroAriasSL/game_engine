#pragma once

#include <example_engine/platform/window.h>
#include <GLFW/glfw3.h>

class MultiPlatformWindow : public Window {
private:
    GLFWwindow* _window;
public:
    MultiPlatformWindow();
    void OpenWindow(WindowData data) override;
    bool Update() override;
};
#pragma once
#define GLFW_INCLUDE_VULKAN

#include <example_engine/platform/window.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace ONI {
class MultiPlatformWindow : public Window {
private:
    GLFWwindow* _window;
public:
    MultiPlatformWindow();
    void OpenWindow(WindowData data) override;
    bool Update() override;
    std::pair<int, int> GetWindowExtents() override;
    void RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) override;
    static inline void errorCallback(int error, const char* description){
        std::cerr << "GLFW Error" << error << description << std::endl;
    }
};
}
#include "multiplatform_window.h"
#include <example_engine/service_locator.h>

namespace ONI {
//Al incializar la ventana se asigna un null pointer a la ventana
MultiPlatformWindow::MultiPlatformWindow(){
    _window = nullptr;
}

/* 
 * Este método abre una ventana utilizando GLFW.
 * 
 * Parámetros:
 *   data: Estructura que contiene la información de la ventana.
 *       - title: Título de la ventana.
 *       - width: Ancho de la ventana.
 *       - height: Alto de la ventana.
 */
void MultiPlatformWindow::OpenWindow(WindowData data){ 

    glfwSetErrorCallback(MultiPlatformWindow::errorCallback);
    
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Desactivar OpenGL para utilizar Vulkan
    //TODO: Definir y proveer un renderer, establecer personalziación y gestión de entrada de usuario
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    _window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
    
    if (!_window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(_window, &_input);

    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
      
      auto* input = static_cast<MultiplatformInput*>(glfwGetWindowUserPointer(window));

      float value = 0.f;

      switch(action){
        case GLFW_PRESS:
        case GLFW_REPEAT:
          value = 1.f;
          break;
        default: 
          value = 0.f;
      }

      input->updateKeyboardState(key, value);
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
      
      auto* input = static_cast<MultiplatformInput*>(glfwGetWindowUserPointer(window));

      if(input) {
        input->updateMouseState(button, action == GLFW_PRESS ? 1.f : 0.f);
      }
    });

    auto* inputListener = ServiceLocator::GetInputListener();

    inputListener->registerDevice(InputDevice {
        .type = InputDeviceType::KEYBOARD,
        .index = 0,
        .stateFunc = std::bind(&MultiplatformInput::getKeyboardState, &_input, std::placeholders::_1)
    });


    inputListener->registerDevice(InputDevice {
        .type = InputDeviceType::MOUSE,
        .index = 0,
        .stateFunc = std::bind(&MultiplatformInput::getMouseState, &_input, std::placeholders::_1)
    });


    glfwMakeContextCurrent(_window);

    glfwSwapInterval(1);
};

//Este método se encarga de registrar los eventos que ocurren en la ventana mediante el contrato de GLFW
bool MultiPlatformWindow::Update(){
    glfwPollEvents();

    return glfwWindowShouldClose(_window);
}

std::pair<int, int> MultiPlatformWindow::GetWindowExtents(){
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);

    return {width, height};
};

void MultiPlatformWindow::RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) {

    try {
        auto vkInstance = std::any_cast<VkInstance>(args[SurfaceArgs::INSTANCE]);
        auto* allocCallBacks = args[SurfaceArgs::ALLOCATORS].has_value() 
          ? std::any_cast<VkAllocationCallbacks*>(args[SurfaceArgs::ALLOCATORS])
          : nullptr; 
        auto* outSurface = std::any_cast<VkSurfaceKHR*>(args[SurfaceArgs::OUT_SURFACE]); 
    
        if (glfwCreateWindowSurface(vkInstance, _window, allocCallBacks, outSurface) != VK_SUCCESS) {
            throw new std::runtime_error("Failed to create window surface!");
        };
    
    } catch (std::bad_any_cast& e) {
        std::cerr << "Failed to cast window surface arguments" << e.what() << std::endl; 
    }
        
}
}
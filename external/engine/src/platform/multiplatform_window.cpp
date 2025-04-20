#include "multiplatform_window.h"

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
    glfwInit();

    // Desactivar OpenGL para utilizar Vulkan
    //TODO: Definir y proveer un renderer, establecer personalziación y gestión de entrada de usuario
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
};

//Este método se encarga de registrar los eventos que ocurren en la ventana mediante el contrato de GLFW
bool MultiPlatformWindow::Update(){
    glfwPollEvents();

    return glfwWindowShouldClose(_window);
};
}
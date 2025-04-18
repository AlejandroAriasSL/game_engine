#include "multiplatform_window.h"

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
    _window = glfwCreateWindow(static_cast<int>(data.width), static_cast<int>(data.height), data.title.c_str(), nullptr, nullptr);
};

//Este método se encarga de registrar los eventos que ocurren en la ventana mediante el contrato de GLFW
bool MultiPlatformWindow::Update(){
    glfwPollEvents();

    return glfwWindowShouldClose(_window);
};
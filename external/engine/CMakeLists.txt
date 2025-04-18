cmake_minimum_required(VERSION 3.20)
project(game VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
# add external libraries 
add_subdirectory(external/glm)
add_subdirectory(external/glfw)

file(GLOB SOURCES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp", "src/*/*/*/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include> #Descarga y ejecuta código de un archivo o módulo
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> #Esta interfaz se lee desde donde quiera que se esté haciendo el build
        glm
    PRIVATE
        glfw
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glm
    PRIVATE
        glfw
)


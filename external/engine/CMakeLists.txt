cmake_minimum_required(VERSION 3.20)
project(game VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
# add external libraries 
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/vk-bootstrap)

find_package(Vulkan REQUIRED)
file(GLOB SOURCES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp", "src/*/*/*/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include> #Descarga y ejecuta código de un archivo o módulo
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> #Esta interfaz se lee desde donde quiera que se esté haciendo el build
        glm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Vulkan_INCLUDE_DIRS}
        glfw
        vk-bootstrap
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glm
    PRIVATE
        ${Vulkan_LIBRARIES}
        glfw
        vk-bootstrap
)

file(GLOB SHADERS shaders/*.frag shaders/*.vert)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/shaders
)

foreach(shader ${SHADERS})
    get_filename_component(SHADER_NAME ${shader} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND glslc -c ${shader} -o ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}.spv
    )
endforeach()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(test)


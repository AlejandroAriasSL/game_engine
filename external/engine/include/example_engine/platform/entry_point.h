#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <example_engine/service_locator.h>

//Keep headers

#include <example_engine/platform/game.hpp>

int main(){
    
    auto* theGame = ONI::CreateGame();

    try {
        theGame->run();
    } catch (const std::exception& e) {
        std::cerr << "Error al abrir la ventana: " << e.what() << std::endl;
        return EXIT_FAILURE;
    };    
    
    delete theGame;
};
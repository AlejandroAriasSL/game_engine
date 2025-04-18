#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <example_engine/service_locator.h>

//Keep headers

#include <example_engine/platform/game.hpp>

int main(){
    
    auto* theGame = CreateGame();

    theGame->run();

    delete theGame;
};
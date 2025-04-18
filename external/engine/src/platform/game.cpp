#include "example_engine/platform/game.hpp"
#include "example_engine/service_locator.h"
#include "multiplatform_window.h"


// Constructor por defecto: Llama al constructor con un solo parámetro para inicializar el título de la ventana a "Game window"
Game::Game() : Game("Game window") {};

// Sobrecarga del constructor: Inicializa la clase Game con un título específico para la ventana.
// También establece el estado de la ventana como "running" y llama a initializeServices para configurar los servicios del juego
Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
    initializeServices();
};

// Destructor de la clase Game: Se asegura de llamar a shutdownServices para liberar los recursos y servicios.
Game::~Game() {
    shutdownServices();
};

// Método principal del juego. Abre la ventana con valores por defecto para el tamaño (800x600) y el título proporcionado.
// Arranca el game loop, que continuará ejecutándose hasta que la ventana se cierre.
void Game::run() {
  ServiceLocator::GetWindow()->OpenWindow({.title = _title, .width = 800, .height = 600});
  
  while(_running) {
     
    if(ServiceLocator::GetWindow()->Update()) {
        _running = false;
        continue;
    }   

    Update(0.0f); // Actualiza el estado del juego
  }
};

// Inicializa los servicios necesarios para el juego, en este caso creando una ventana multiplataforma.
void Game::initializeServices() {
  ServiceLocator::Provide(new MultiPlatformWindow());
};

// Destruye los servicios y limpia los recursos utilizados por el juego.
void Game::shutdownServices() {
  ServiceLocator::ShutdownServices();
};
#pragma once
#include <memory>
#include <example_engine/platform/window.h>
#include <example_engine/rendering/renderer.h>
#include <example_engine/input/input_listener.h>

/*
*  La clase ServiceLocator es responsable de gestionar la instancia única de la ventana del juego.
* Tiene tres métodos principales:
*  - Provide: Recibe un puntero a un objeto tipo ventana. Si la ventana ya se ha proporcinado, no hace nada.
   - GetWindow: Devuelve una referencia a la ventana, si no ha sido proporcionada, devuelve nullptr.
   - ShutdownServices: Limpia los servicios, en particular, borra la referencia a la ventana.   
*/ 

namespace ONI {
  class ServiceLocator{
    public:
      static inline Window* GetWindow() { return _window.get(); }
      static inline Renderer* GetRenderer() { return _renderer.get(); }
      static inline InputListener* GetInputListener() { return _inputListener.get(); } 

    static inline void Provide(Window* window) {
      if (_window != nullptr) return;
      _window = std::unique_ptr<Window>(window);
    }
 
    static inline void Provide(Renderer* renderer, RendererSettings settings) {
      if (_renderer != nullptr) return;
      _renderer = std::unique_ptr<Renderer>(renderer);        
      _renderer->Init(settings);
    }

    static inline void Provide(InputListener* inputListener ) {
      if (_inputListener != nullptr) return;
      _inputListener = std::unique_ptr<InputListener>(inputListener);
    }
 
    static inline void ShutdownServices() {
      shutdownInputListener();
      shutdownRenderer();
      shutdownWindow();
    }
 
    private:
      static inline std::unique_ptr<Window> _window = nullptr;
      static inline std::unique_ptr<Renderer> _renderer = nullptr;
      static inline std::unique_ptr<InputListener> _inputListener = nullptr;
 
    static inline void shutdownWindow() {
      _window.reset();
    }

    static inline void shutdownRenderer() {
      if (!_renderer) return;
      _renderer->Shutdown();
      _renderer.reset();
    }

    static inline void shutdownInputListener() {
      if (!_inputListener) return;
      _inputListener.reset();
    }
  };
}
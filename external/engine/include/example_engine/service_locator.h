#pragma once
#include <memory>
#include <example_engine/platform/window.h>
#include <example_engine/rendering/renderer.h>

/*
*  La clase ServiceLocator es responsable de gestionar la instancia única de la ventana del juego.
* Tiene tres métodos principales:
*  - Provide: Recibe un puntero a un objeto tipo ventana. Si la ventana ya se ha proporcinado, no hace nada.
   - GetWindow: Devuelve una referencia a la ventana, si no ha sido proporcionada, devuelve nullptr.
   - ShutdownServices: Limpia los servicios, en particular, borra la referencia a la ventana.   
*/ 

namespace ONI {
class ServiceLocator{
private:
    static inline std::unique_ptr<Window> _window = nullptr;
    static inline std::unique_ptr<Renderer> _renderer = nullptr;
    
    static inline void shutdownWindow() {
        _window.reset();
    }

    static inline void shutdownRenderer() {
        if (!_renderer) return;
        _renderer->Shutdown();
        _renderer.reset();
    }
public:
    static inline const std::unique_ptr<Window>& GetWindow() { return _window; }
    static inline const std::unique_ptr<Renderer>& GetRenderer() { return _renderer; }

    static inline void Provide(Window* window) {
        if (_window != nullptr) return;
        _window = std::unique_ptr<Window>(window);
    }

    static inline void Provide(Renderer* renderer, RendererSettings settings) {
        if (_renderer != nullptr) return;
        _renderer = std::unique_ptr<Renderer>(renderer);        
        _renderer->Init(settings);
    };

    static inline void ShutdownServices() {
        shutdownRenderer();
        shutdownWindow();
    }
};
}
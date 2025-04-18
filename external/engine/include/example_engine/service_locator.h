#pragma once
#include <memory>
#include <example_engine/platform/window.h>

/*
*  La clase ServiceLocator es responsable de gestionar la instancia única de la ventana del juego.
* Tiene tres métodos principales:
*  - Provide: Recibe un puntero a un objeto tipo ventana. Si la ventana ya se ha proporcinado, no hace nada.
   - GetWindow: Devuelve una referencia a la ventana, si no ha sido proporcionada, devuelve nullptr.
   - ShutdownServices: Limpia los servicios, en particular, borra la referencia a la ventana.   
*/ 
class ServiceLocator{
private:
    static inline std::unique_ptr<Window> _window = nullptr;
    
    static inline void shutdownWindow() {
        _window.reset();
        _window = nullptr;
    }
public:
    static inline const std::unique_ptr<Window>& GetWindow() { return _window; }

    static inline void Provide(Window* window) {
        if (_window != nullptr) return;
        _window = std::unique_ptr<Window>(window);
    }

    static inline void ShutdownServices() {
        shutdownWindow();
    }
};
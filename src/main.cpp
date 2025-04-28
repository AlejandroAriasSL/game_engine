#include <example_engine/platform/entry_point.h>
#include <example_engine/platform/game.hpp>

using namespace ONI;

class ExampleGame : public Game {
public:
  explicit ExampleGame(std::string title) : Game(std::move(title)) {
    std::cout << "Hello, Example game!" << std::endl;

    _inputListener = ServiceLocator::GetInputListener();

    if(_inputListener){
      _inputListener->mapInputToAction(InputKey::A, InputAction {
        .actionName = "speedup",
        .scale = -1.f
      });
      _inputListener->mapInputToAction(InputKey::D, InputAction {
        .actionName = "speedup",
        .scale = 1.f
      });

      _inputListener->registerActionCallback("speedup", InputListener::ActionCallback {
        .ref = "ExampleGame",
        .func = [](InputSource source, int sourceIndex, float value){
          std::cout << "speeding" << (value == 1.f ? "RIGHT" : "LEFT") << std::endl;
          return true;
        }
      });
    }
  }

  protected:
    void Update(float deltaTime) override {
    
    }

  private:
    InputListener* _inputListener {nullptr};
};


Game* ONI::CreateGame() {
    return new ExampleGame("Game Window");
};
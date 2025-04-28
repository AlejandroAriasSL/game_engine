#include <example_engine/platform/entry_point.h>
#include <example_engine/platform/game.hpp>

using namespace ONI;

class ExampleGame : public Game {
public:
  explicit ExampleGame(std::string title) : Game(std::move(title)) {
    std::cout << "Hello, Example game!" << std::endl;
  }

protected:
  void Update(float deltaTime) override {
  }
};


Game* ONI::CreateGame() {
    return new ExampleGame("Game Window");
};
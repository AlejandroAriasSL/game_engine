#include <example_engine/platform/entry_point.h>
#include <example_engine/platform/game.hpp>

class ExampleGame : public Game {
public:
  explicit ExampleGame(std::string title) : Game(std::move(title)) {
    std::cout << "Hello, Example game!" << std::endl;
  }

protected:
  void Update(float deltaTime) override {
    std::cout << "I'm updating!" << std::endl;
  }
};


Game* CreateGame() {
    return new ExampleGame("Game Window");
};
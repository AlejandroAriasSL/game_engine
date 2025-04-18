#pragma once
#include <string>
//Queremos darle acceso a nuestro main.cpp (nuestro cliente) para que pueda crear juegos utilizando nuestro motor 

class Game {
protected:
  virtual void PhysicsUpdate(float deltaTTime) {};
  virtual void Update(float deltaTTime) {};
private:
  void initializeServices();
  void shutdownServices();
public:
  Game();
  explicit Game(std::string windowTitle); 

  ~Game();

  void run();

private:
  std::string _title;
  bool _running;
};

extern Game* CreateGame();
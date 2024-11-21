#pragma once
#include "kalah.hpp"

class Game {
private:
  Kalah kalah_;

public:
  Game(int numHouses, int numSeeds) : kalah_(numHouses, numSeeds){};

  // implement game logic
  void displayBoard();
  void playGame();
};

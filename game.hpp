#pragma once
#include "kalah.hpp"

class Game {
private:
  Kalah kalah_;
  int maxMove_;

public:
  Game(int numHouses, int numSeeds)
      : kalah_(numHouses, numSeeds), maxMove_(numHouses){};

  // implement game logic
  void displayBoard();
  void playGame();
};

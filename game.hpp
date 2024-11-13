#pragma once
#include "kalah.hpp"
#include "player.hpp"

class Game {
private:
  Kalah kalah_;

  Player checkTurn();
  bool isGameOver();
  void captureSeeds();

public:
  Game(int numHouses, int numSeeds) : kalah_(numHouses, numSeeds){};

  // implement game logic
  void displayBoard() { kalah_.showBoard(); }
  void playGame();
};

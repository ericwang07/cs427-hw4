#pragma once
#include "kalah.hpp"

class Game {
private:
  Kalah kalah_;
  void printInfo();
  bool askValidMove(int &move);
  void executeMove(int move);
  void finishGame();

public:
  Game(int numHouses, int numSeeds) : kalah_(numHouses, numSeeds){};
  void playGame();
};

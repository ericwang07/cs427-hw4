#pragma once
#include "board.hpp"
#include "outcome.hpp"
#include "player.hpp"

class Kalah {
private:
  Player northPlayer_;
  Player southPlayer_;
  Player *currPlayer_;

  Board board_;

  // move results
  bool anotherTurn_;
  int seedsCaptured_;

  // game results
  int northSeeds_;
  int southSeeds_;
  Outcome outcome_;

  void switchPlayer();

public:
  Kalah(int numHouses, int numSeeds);
  ~Kalah() = default;

  bool isValidMove(int move);
  bool isOver();
  void endGame();

  void doMove(int move);
  void showBoard();

  bool getAnotherTurn();
  int getSeedsCaptured();

  int getNorthSeeds();
  int getSouthSeeds();
  Outcome getOutcome();

  string getCurrPlayer();
};

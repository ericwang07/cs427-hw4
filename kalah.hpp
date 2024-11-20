#pragma once
#include "board.cpp"
#include "player.hpp"
#include <iostream>

class Kalah {
private:
  Player northPlayer_;
  Player southPlayer_;
  Player *currPlayer_;
  Board board_;

  bool anotherTurn_;
  bool wasCaptured_;
  int seedsCaptured_;

  Player checkTurn();
  void captureSeeds();

public:
  Kalah(int numHouses, int numSeeds)
      : northPlayer_({Side::North, "North", "N"}),
        southPlayer_({Side::South, "South", "S"}), currPlayer_(&southPlayer_),
        board_(Board(numHouses, numSeeds, &northPlayer_, &southPlayer_)){};
  ~Kalah() = default;
  // implement game logic
  bool isOver();
  string getCurrPlayer();
  bool getAnotherTurn();
  bool getWasCaptured();
  int getSeedsCaptured();
  void doMove(int move);
  void showBoard() { cout << board_ << endl; };
};

// doMove requirements
// - call board.sowSeeds(int move);
// - grab all seeds from pit
// - while n is not 0: deposit 1 in pit
//
// Board getIndex(move):
//
//
// Board sowSeeds(int move)
// - index = board.getIndex(int move)
// - while n > 0:
// -  currPit.drop(1)
// -  currPit = currPit.getNext()
//

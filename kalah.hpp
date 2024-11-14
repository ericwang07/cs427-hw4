#pragma once
#include "board.cpp"
#include "player.hpp"
#include <iostream>
#include <memory>

class Kalah {
private:
  std::shared_ptr<Player> northPlayer_;
  std::shared_ptr<Player> southPlayer_;
  std::shared_ptr<Player> currPlayer_;
  Board board_;
  // Player nextPlayer_;
  // int seedArr_[];

  Player checkTurn();
  void captureSeeds();

public:
  Kalah(int numHouses, int numSeeds)
      : northPlayer_(std::make_shared<Player>(Side::North, "North", "N")),
        southPlayer_(std::make_shared<Player>(Side::South, "South", "S")),
        currPlayer_(southPlayer_),
        board_(Board(numHouses, numSeeds, northPlayer_, southPlayer_)){};
  ~Kalah() = default;
  // implement game logic
  bool isOver();
  // bool isValidMove(int move);
  // void doMove(int move);
  // int numCaptured();
  void showBoard() { cout << board_ << endl; };
};

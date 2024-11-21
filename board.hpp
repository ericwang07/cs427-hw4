/*
 * Board.hpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#pragma once
#include "pit.hpp"
#include "player.hpp"
#include <memory>

class Board {
private:
  const int h_;
  const int maxSeeds_;
  Player *northPlayer_;
  Player *southPlayer_;
  std::unique_ptr<Pit[]> pitWarehouse_;
  void createPits(int);
  int findIndex(int move, Side side);
  int findStoreIndex(Side side);
  // void checkCapture(int index);
  void printHouses(Side side, std::ostream &out);

public:
  Board(int numHouses, int initSeeds, Player *northPlayer, Player *southPlayer);
  ~Board() = default;
  std::ostream &print(std::ostream &out) const;
  void run() const;
  int sowSeeds(int n, Side side, Pit *startPit);
  void collectRemaining(Side side, Side otherSide);
  Pit *getPit(int move, Side side);
  Pit *getStore(Side side);
  Player *getWinner();
  int getNorthTotal();
  int getSouthTotal();
  int grabRow(Side side);
};

inline std::ostream &operator<<(std::ostream &out, const Board &b) {
  return b.print(out);
}

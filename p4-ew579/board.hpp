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
  int sumNorthHouses();
  int sumSouthHouses();
  void printHouseLabels(std::ostream &os,
                        std::ostringstream &ss,
                        Side side) const;
  void printHouseSeeds(std::ostream &os,
                       std::ostringstream &ss,
                       Side side) const;
  void printStores(std::ostream &os,
                   std::ostringstream &ss) const;

public:
  Board(int numHouses, int initSeeds, Player *northPlayer,
        Player *southPlayer);
  ~Board() = default;
  int sowAndCapture(int n, Side side, Pit *startPit);
  void collectRemaining(Side side);
  int grabRow(Side side);
  int getStoreSeeds(Side side);
  bool isTerminal();
  bool isMoveInRange(int move);
  Pit *getPit(int move, Side side);
  std::ostream &print(std::ostream &os) const;
};

inline std::ostream &operator<<(std::ostream &os,
                                const Board &b) {
  return b.print(os);
}

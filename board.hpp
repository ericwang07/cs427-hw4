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
  Player northPlayer_;
  Player southPlayer_;
  std::unique_ptr<Pit[]> pitWarehouse_;
  void createPits(int);

public:
  Board(int numHouses, int initSeeds);
  ~Board() = default;
  std::ostream &print(std::ostream &out) const;
  void run() const;
};

inline std::ostream &operator<<(std::ostream &out,
                                const Board &b) {
  return b.print(out);
}

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
  std::shared_ptr<Player> northPlayer_;
  std::shared_ptr<Player> southPlayer_;
  std::unique_ptr<Pit[]> pitWarehouse_;
  void createPits(int);

public:
  Board(int numHouses, int initSeeds, std::shared_ptr<Player> northPlayer,
        std::shared_ptr<Player> southPlayer);
  ~Board() = default;
  std::ostream &print(std::ostream &out) const;
  void run() const;
};

inline std::ostream &operator<<(std::ostream &out, const Board &b) {
  return b.print(out);
}

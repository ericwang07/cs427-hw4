/*
 * Board.cpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#include "board.hpp"
#include "pit.hpp"
#include "player.hpp"
#include <memory>

Board::Board(int numHouses, int numSeeds, std::shared_ptr<Player> northPlayer,
             std::shared_ptr<Player> southPlayer)
    : h_(numHouses), northPlayer_(northPlayer), southPlayer_(southPlayer),
      pitWarehouse_(std::make_unique<Pit[]>(2 * h_ + 2)) {
  createPits(numSeeds);
};

void Board::createPits(int initSeeds) {
  int totalPits = 2 * h_ + 2;
  for (int i = 0; i < totalPits; i++) {
    shared_ptr<Player> owner = i < h_ + 1 ? southPlayer_ : northPlayer_;
    int id = h_ - (i % (h_ + 1));
    Pit *next = i == totalPits - 1 ? &pitWarehouse_[0] : &pitWarehouse_[i + 1];
    Pit *opposite =
        (i == h_ || i == totalPits - 1) ? nullptr : &pitWarehouse_[2 * h_ - i];
    int seeds = (i == h_ || i == totalPits - 1) ? 0 : initSeeds;

    Pit tempPit(owner, id, next, opposite, seeds);
    pitWarehouse_[i] = std::move(tempPit);
  }
}

std::ostream &Board::print(std::ostream &out) const {
  out << "Printing Board" << std::endl;
  out << "Starting pit S" << h_ << std::endl;
  for (int i = 0; i < 2 * h_ + 2; i++) {
    out << pitWarehouse_[i];
  }
  out << "Exiting Board::print()" << std::endl;
  return out;
}

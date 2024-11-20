/*
 * Board.cpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#include "board.hpp"
#include "pit.hpp"
#include "player.hpp"
#include <iomanip>
#include <memory>
#include <sstream>

Board::Board(int numHouses, int numSeeds, Player *northPlayer,
             Player *southPlayer)
    : h_(numHouses), maxSeeds_(2 * numHouses * numSeeds),
      northPlayer_(northPlayer), southPlayer_(southPlayer),
      pitWarehouse_(std::make_unique<Pit[]>(2 * h_ + 2)) {
  createPits(numSeeds);
};

int Board::findIndex(int move, Side side) {
  return side == Side::South ? h_ - move : 2 * h_ - move + 1;
}

int Board::findStoreIndex(Side side) {
  return side == Side::South ? h_ : 2 * h_ - 1;
}

void Board::createPits(int initSeeds) {
  int totalPits = 2 * h_ + 2;
  for (int i = 0; i < totalPits; i++) {
    Player *owner = i < h_ + 1 ? southPlayer_ : northPlayer_;
    int id = h_ - (i % (h_ + 1));
    Pit *next = i == totalPits - 1 ? &pitWarehouse_[0] : &pitWarehouse_[i + 1];
    Pit *opposite =
        (i == h_ || i == totalPits - 1) ? nullptr : &pitWarehouse_[2 * h_ - i];
    int seeds = (i == h_ || i == totalPits - 1) ? 0 : initSeeds;

    Pit tempPit(owner, id, next, opposite, seeds, maxSeeds_);
    pitWarehouse_[i] = std::move(tempPit);
  }
}

int Board::sowSeeds(int move, Player *player) {
  int index = findIndex(move, player->side);
  int storeIndex = findStoreIndex(player->side);

  int n = pitWarehouse_[index].grab();
  Pit *currPit = pitWarehouse_[index].getNext();

  while (n > 0) {
    if (currPit->isOppositeStore(player->side)) {
      continue;
    }

    currPit->drop(1);
    n--;

    if (n == 0) { // done dropping last stone
      if (currPit->isSameStore(player->side)) {
        return -1; // current player gets another turn
      }

      int captured = currPit->captureOpposite(player->side);
      pitWarehouse_[storeIndex].drop(captured);
      return captured;
    }

    currPit = currPit->getNext();
  }

  return 0; // return the other player
}

bool Board::isTerminal() {
  return pitWarehouse_[h_].getSeeds() + pitWarehouse_[2 * h_ + 1].getSeeds() ==
         maxSeeds_;
};

std::ostream &Board::print(std::ostream &out) const {
  std::ostringstream ss;

  // south logic
  ss << setw(11) << " ";
  for (int i = 2 * h_; i > h_; i--) {
    ss << pitWarehouse_[i].getLabel();
    if (i != h_ + 1) {
      ss << setw(4) << " ";
    }
  }
  out << ss.str() << std::endl;
  ss.str("");

  ss << setw(10) << " ";
  for (int i = 2 * h_; i > h_; i--) {
    ss << "[" << setw(2) << pitWarehouse_[i].getSeeds() << "]";
    if (i != h_ + 1) {
      ss << setw(2) << " ";
    }
  }
  out << ss.str() << std::endl;
  ss.str("");

  // center logic
  Pit &northStore = pitWarehouse_[2 * h_ + 1];
  Pit &southStore = pitWarehouse_[h_];
  ss << setw(2) << " ";
  ss << northStore.getLabel();
  ss << setw(1) << " ";
  ss << "[" << setw(2) << northStore.getSeeds() << "]";
  ss << setw(36) << " ";
  ss << "[" << setw(2) << southStore.getSeeds() << "]";
  ss << setw(1) << " ";
  ss << southStore.getLabel();
  out << ss.str() << std::endl;
  ss.str("");

  // south logic

  ss << setw(10) << " ";
  for (int i = 0; i < h_; i++) {
    ss << "[" << setw(2) << pitWarehouse_[i].getSeeds() << "]";
    if (i != h_ - 1) {
      ss << setw(2) << " ";
    }
  }
  out << ss.str() << std::endl;
  ss.str("");

  ss << setw(11) << " ";
  for (int i = 0; i < h_; i++) {
    ss << pitWarehouse_[i].getLabel();
    if (i != h_ - 1) {
      ss << setw(4) << " ";
    }
  }
  out << ss.str() << std::endl;
  ss.str("");
  return out;
}

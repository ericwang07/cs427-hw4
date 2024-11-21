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

Pit *Board::getPit(int move, Side s) {
  int index = findIndex(move, s);
  return &pitWarehouse_[index];
}

Pit *Board::getStore(Side s) {
  if (s == Side::South) {
    return &pitWarehouse_[h_];
  } else {
    return &pitWarehouse_[2 * h_ + 1];
  }
}

int Board::sowSeeds(int n, Side side, Pit *startPit) {
  int storeIndex = findStoreIndex(side); // NOTE: find another way to get stores

  Pit *currPit = startPit->getNext();

  while (n > 0) {
    if (currPit->isOppositeStore(side)) {
      continue;
    }

    currPit->drop(1);
    n--;

    if (n == 0) { // done dropping last stone
      if (currPit->isSameStore(side)) {
        return -1; // current player gets another turn
      }

      int captured = currPit->captureOpposite(side);
      pitWarehouse_[storeIndex].drop(captured);
      return captured;
    }

    currPit = currPit->getNext();
  }

  return 0; // return the other player
}

void Board::collectRemaining(Side side, Side otherSide) {
  int captured = grabRow(side);
  int storeIndex =
      findStoreIndex(otherSide); // NOTE: find another way to get stores
  pitWarehouse_[storeIndex].drop(captured);
}

int Board::getNorthTotal() {
  int n = 0;
  for (int i = h_ + 1; i < 2 * h_ + 1; i++) { // North
    n += pitWarehouse_[i].getSeeds();
  }

  return n;
};

int Board::getSouthTotal() {
  int n = 0;
  for (int i = 0; i < h_; i++) { // South
    n += pitWarehouse_[i].getSeeds();
  }

  return n;
};

int Board::grabRow(Side side) {
  int n = 0;
  if (side == Side::South) {
    for (int i = 0; i < h_; i++) { // South
      n += pitWarehouse_[i].grab();
    }
  } else {
    for (int i = h_ + 1; i < 2 * h_ + 1; i++) { // North
      n += pitWarehouse_[i].grab();
    }
  }

  return n;
}

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

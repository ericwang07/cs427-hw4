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

void Board::createPits(int initSeeds) {
  int totalPits = 2 * h_ + 2;
  for (int i = 0; i < totalPits; i++) {
    Player *owner = i < h_ + 1 ? southPlayer_ : northPlayer_;
    int id = h_ - (i % (h_ + 1));
    Pit *next = i == totalPits - 1 ? &pitWarehouse_[0]
                                   : &pitWarehouse_[i + 1];
    Pit *opposite = (i == h_ || i == totalPits - 1)
                        ? nullptr
                        : &pitWarehouse_[2 * h_ - i];
    int seeds =
        (i == h_ || i == totalPits - 1) ? 0 : initSeeds;

    Pit tempPit(owner, id, next, opposite, seeds, maxSeeds_);
    pitWarehouse_[i] = std::move(tempPit);
  }
}

int Board::findIndex(int move, Side side) {
  return side == Side::South ? h_ - move : 2 * h_ - move + 1;
}

int Board::findStoreIndex(Side side) {
  return side == Side::South ? h_ : 2 * h_ + 1;
}

int Board::sumNorthHouses() {
  int n = 0;
  for (int i = h_ + 1; i < 2 * h_ + 1; i++) {
    n += pitWarehouse_[i].getSeeds();
  }

  return n;
};

int Board::sumSouthHouses() {
  int n = 0;
  for (int i = 0; i < h_; i++) {
    n += pitWarehouse_[i].getSeeds();
  }

  return n;
};

void Board::printHouseLabels(std::ostream &os,
                             std::ostringstream &ss,
                             Side side) const {
  if (side == Side::North) {
    // south logic
    ss << setw(11) << " ";
    for (int i = 2 * h_; i > h_; i--) {
      ss << pitWarehouse_[i].getLabel();
      if (i != h_ + 1) {
        ss << setw(4) << " ";
      }
    }
    os << ss.str() << std::endl;
    ss.str("");
  } else {

    ss << setw(11) << " ";
    for (int i = 0; i < h_; i++) {
      ss << pitWarehouse_[i].getLabel();
      if (i != h_ - 1) {
        ss << setw(4) << " ";
      }
    }
    os << ss.str() << std::endl;
    ss.str("");
  }
  return;
}

void Board::printHouseSeeds(std::ostream &os,
                            std::ostringstream &ss,
                            Side side) const {
  if (side == Side::North) {
    ss << setw(10) << " ";
    for (int i = 2 * h_; i > h_; i--) {
      ss << "[" << setw(2) << pitWarehouse_[i] << "]";
      if (i != h_ + 1) {
        ss << setw(2) << " ";
      }
    }
    os << ss.str() << std::endl;
    ss.str("");
  } else {
    ss << setw(10) << " ";
    for (int i = 0; i < h_; i++) {
      ss << "[" << setw(2) << pitWarehouse_[i] << "]";
      if (i != h_ - 1) {
        ss << setw(2) << " ";
      }
    }
    os << ss.str() << std::endl;
    ss.str("");
  }
}

void Board::printStores(std::ostream &os,
                        std::ostringstream &ss) const {

  Pit &northStore = pitWarehouse_[2 * h_ + 1];
  Pit &southStore = pitWarehouse_[h_];
  int middleMargin = h_ * 6;
  ss << setw(2) << " ";
  ss << northStore.getLabel();
  ss << setw(1) << " ";
  ss << "[" << setw(2) << northStore << "]";
  ss << setw(middleMargin) << " ";
  ss << "[" << setw(2) << southStore << "]";
  ss << setw(1) << " ";
  ss << southStore.getLabel();
  os << ss.str() << std::endl;
  ss.str("");
}

int Board::sowAndCapture(int n, Side side, Pit *startPit) {
  int storeIndex = findStoreIndex(side);

  Pit *currPit = startPit->getNext();

  while (n > 0) {
    if (currPit->isOppositeStore(side)) {
      std::cout << "opposite store detected" << std::endl;
      currPit = currPit->getNext();
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

void Board::collectRemaining(Side side) {
  int remainingSeeds = grabRow(side);
  int storeIndex = findStoreIndex(side);
  pitWarehouse_[storeIndex].drop(remainingSeeds);
  return;
}

int Board::getStoreSeeds(Side side) {
  int storeIndex = findStoreIndex(side);
  return pitWarehouse_[storeIndex].getSeeds();
}

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

bool Board::isTerminal() {
  return sumNorthHouses() == 0 || sumSouthHouses() == 0;
}

bool Board::isMoveInRange(int move) {
  return move > 0 && move <= h_;
} // only houses

Pit *Board::getPit(int move, Side s) {
  int index = findIndex(move, s);
  return &pitWarehouse_[index];
}

std::ostream &Board::print(std::ostream &os) const {
  std::ostringstream ss;

  printHouseLabels(os, ss, Side::North);
  printHouseSeeds(os, ss, Side::North);

  printStores(os, ss);

  printHouseSeeds(os, ss, Side::South);
  printHouseLabels(os, ss, Side::South);

  return os;
}

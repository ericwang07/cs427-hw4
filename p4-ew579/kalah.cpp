#include "kalah.hpp"
#include "outcome.hpp"
#include "player.hpp"
#include <iostream>

Kalah::Kalah(int numHouses, int numSeeds)
    : northPlayer_({Side::North, "North", "N"}),
      southPlayer_({Side::South, "South", "S"}),
      currPlayer_(&southPlayer_),
      board_(Board(numHouses, numSeeds, &northPlayer_,
                   &southPlayer_)) {}

void Kalah::switchPlayer() {
  currPlayer_ = currPlayer_->side == Side::South
                    ? &northPlayer_
                    : &southPlayer_;
}

bool Kalah::isValidMove(int move) {
  bool inRange = board_.isMoveInRange(move);
  bool isEmpty =
      board_.getPit(move, currPlayer_->side)->getSeeds() == 0;
  if (isEmpty) {
    std::cout << "Can't choose an empty pit" << std::endl;
  }
  return inRange && !isEmpty;
};

bool Kalah::isOver() { return board_.isTerminal(); };

void Kalah::endGame() {
  board_.collectRemaining(Side::North);
  board_.collectRemaining(Side::South);
  northSeeds_ = board_.getStoreSeeds(Side::North);
  southSeeds_ = board_.getStoreSeeds(Side::South);
  if (northSeeds_ > southSeeds_) {
    outcome_ = Outcome::NorthWin;
  } else if (northSeeds_ < southSeeds_) {
    outcome_ = Outcome::SouthWin;
  } else {
    outcome_ = Outcome::Tie;
  }
}

void Kalah::doMove(int move) {
  Pit *pit = board_.getPit(move, currPlayer_->side);
  int n = pit->grab();

  int captured =
      board_.sowAndCapture(n, currPlayer_->side, pit);
  if (captured == -1) { // player gets another turn
    anotherTurn_ = true;
    seedsCaptured_ = 0;
  } else {
    switchPlayer();
    anotherTurn_ = false;
    seedsCaptured_ = captured;
  }
  return;
}

void Kalah::showBoard() { cout << board_ << endl; };

bool Kalah::getAnotherTurn() { return anotherTurn_; };
int Kalah::getSeedsCaptured() { return seedsCaptured_; };

Outcome Kalah::getOutcome() { return outcome_; };
int Kalah::getNorthSeeds() { return northSeeds_; };
int Kalah::getSouthSeeds() { return southSeeds_; };

string Kalah::getCurrPlayer() { return currPlayer_->name; };

#include "kalah.hpp"
#include "outcome.hpp"
#include <iostream>
#include <stdexcept>

void Kalah::doMove(int move) {
  Pit *pit = board_.getPit(move, currPlayer_->side);
  int n = pit->grab();

  int captured = board_.sowSeeds(n, currPlayer_->side, pit);
  if (captured == -1) {
    anotherTurn_ = true;
    wasCaptured_ = false;
    seedsCaptured_ = 0;
  } else {
    currPlayer_ =
        currPlayer_->side == Side::South ? &northPlayer_ : &southPlayer_;
    anotherTurn_ = false;
    wasCaptured_ = captured > 0 ? true : false;
    seedsCaptured_ = captured;
  }
  return;
}

bool Kalah::isValidMove(int move) {
  if (move > 0 && move <= maxMove_) {
    if (board_.getPit(move, currPlayer_->side)->isEmpty()) {
      std::cout << "Can't choose an empty pit" << std::endl;
      return false;
    }
    return true;
  }
  return false;
};

bool Kalah::isOver() {
  int northTotal = board_.getNorthTotal();
  int southTotal = board_.getSouthTotal();

  if (northTotal == 0) {
    emptyPlayer_ = &northPlayer_;
    return true;
  } else if (southTotal == 0) {
    emptyPlayer_ = &southPlayer_;
    return true;
  }

  return false;
};

void Kalah::endGame() {
  board_.collectRemaining(emptyPlayer_->otherSide(), emptyPlayer_->side);
  northSeeds_ = board_.getStore(Side::North)->getSeeds();
  southSeeds_ = board_.getStore(Side::South)->getSeeds();
  if (northSeeds_ > southSeeds_) {
    outcome_ = Outcome::NorthWin;
  } else if (northSeeds_ < southSeeds_) {
    outcome_ = Outcome::SouthWin;
  } else {
    outcome_ = Outcome::Tie;
  }
}

string Kalah::getCurrPlayer() { return currPlayer_->name; };
bool Kalah::getAnotherTurn() { return anotherTurn_; };
bool Kalah::getWasCaptured() { return wasCaptured_; };
int Kalah::getSeedsCaptured() { return seedsCaptured_; };

Outcome Kalah::getOutcome() { return outcome_; };
int Kalah::getNorthSeeds() { return northSeeds_; };
int Kalah::getSouthSeeds() { return southSeeds_; };

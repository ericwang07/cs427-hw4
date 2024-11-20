#include "kalah.hpp"

void Kalah::doMove(int move) {
  int captured = board_.sowSeeds(move, currPlayer_);
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

bool Kalah::isOver() { return board_.isTerminal(); };

string Kalah::getCurrPlayer() { return currPlayer_->name; };
bool Kalah::getAnotherTurn() { return anotherTurn_; };
bool Kalah::getWasCaptured() { return wasCaptured_; };
int Kalah::getSeedsCaptured() { return seedsCaptured_; };
// bool Kalah::isValidMove(int move) {
//   if (1 <= move && move <= 6 && board_.) { }
//   return false;
// }

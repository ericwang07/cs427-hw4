/*
 * Pit.cpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#include "pit.hpp"
#include <iostream>

Pit::Pit() // default constructor
    : seeds_(0), maxSeeds_(0), next_(nullptr),
      opposite_(nullptr), label_("") {}

Pit::Pit(Player *owner, int id, Pit *next, Pit *opposite,
         int seeds, int maxSeeds)
    : seeds_(seeds), maxSeeds_(maxSeeds), next_(next),
      opposite_(opposite),
      label_(owner->code + std::to_string(id)), owner_(owner) {
}

bool Pit::isStore() { return opposite_ == nullptr; }

int Pit::grab() {
  int grabbed = seeds_;
  seeds_ = 0;
  return grabbed;
};

void Pit::drop(int n) {
  if (n > 0 && n + seeds_ <= maxSeeds_) {
    seeds_ += n;
  }
};

int Pit::captureOpposite(Side side) {
  if (side == owner_->side && seeds_ == 1 &&
      opposite_->seeds_ > 0) {
    int oppSeeds = opposite_->grab();
    int seeds = grab();
    return seeds + oppSeeds;
  }
  return 0;
};

bool Pit::isOppositeStore(Side side) {
  return side != owner_->side && isStore();
}

bool Pit::isSameStore(Side side) {
  return side == owner_->side && isStore();
}

Pit *Pit::getNext() { return next_; }
int Pit::getSeeds() { return seeds_; }

std::string Pit::getLabel() { return label_; }

ostream &Pit::print(ostream &out) const {
  out << seeds_;
  return out;
}

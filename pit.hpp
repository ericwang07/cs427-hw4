/*
 * Pit.hpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#pragma once
#include "player.hpp"
#include <iostream>
#include <string>

class Pit {
private:
  int seeds_;
  int maxSeeds_;
  Pit *next_;
  Pit *opposite_;
  std::string label_;
  Player *player_; // NOTE: remove
  bool isStore_() { return opposite_ == nullptr; }

public:
  Pit() // default constructor
      : seeds_(0), maxSeeds_(0), next_(nullptr), opposite_(nullptr),
        label_("") {}
  Pit(Player *player, int id, Pit *next, Pit *opposite, int seeds, int maxSeeds)
      : seeds_(seeds), maxSeeds_(maxSeeds), next_(next), opposite_(opposite),
        label_(player->code + std::to_string(id)), player_(player) {}
  ~Pit() = default;
  int grab() {
    int grabbed = seeds_;
    seeds_ = 0;
    return grabbed;
  };
  void drop(int n) {
    if (n > 0 && n + seeds_ <= maxSeeds_) {
      seeds_ += n;
    }
  };

  Pit *getNext() { return next_; }
  string getLabel() { return label_; }
  int getSeeds() { return seeds_; }
  bool isOppositeStore(Side side) {
    return side != player_->side && isStore_();
  }
  bool isSameStore(Side side) { return side == player_->side && isStore_(); }

  int captureOpposite(Side side) {
    if (side == player_->side && seeds_ == 1 && opposite_->seeds_ > 0) {
      int collected = seeds_ + opposite_->seeds_;
      seeds_ = 0;
      opposite_->seeds_ = 0;
      return collected;
    }
    return 0;
  };
  ostream &print(ostream &out) const {
    out << "pit[" << label_ << "]: ";
    out << seeds_ << " seeds, ";
    out << "next->[" << next_->label_ << "], ";
    out << "opposite";
    opposite_ ? out << "->[" << opposite_->label_ << "]" << endl
              : out << " = nullptr" << endl;
    return out;
  }
};

inline ostream &operator<<(ostream &out, const Pit &p) { return p.print(out); }

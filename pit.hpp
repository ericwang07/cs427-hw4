/*
 * Pit.hpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#pragma once
#include "player.hpp"
#include <iostream>
#include <memory>
#include <string>

class Pit {
private:
  shared_ptr<Player> owner_; // NOTE: remove
  std::string label_;
  Pit *next_;
  Pit *opposite_;
  int seeds_;
  // NOTE: seeds member variable should be included and
  // initialized, but due to it not being used, a compiler will
  // throw a warning, so it is omitted for this assignment

public:
  Pit() // default constructor
      : owner_(nullptr), label_(""), next_(nullptr), opposite_(nullptr),
        seeds_(0) {}
  Pit(shared_ptr<Player> player, int id, Pit *next, Pit *opposite, int seeds)
      : owner_(player), label_(owner_->code + std::to_string(id)), next_(next),
        opposite_(opposite), seeds_(seeds) {}
  ~Pit() = default;

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

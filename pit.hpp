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
  int seeds_;
  Pit *next_;
  Pit *opposite_;
  std::string label_;
  shared_ptr<Player> owner_; // NOTE: remove
public:
  Pit() // default constructor
      : seeds_(0), next_(nullptr), opposite_(nullptr), label_(""),
        owner_(nullptr) {}
  Pit(shared_ptr<Player> player, int id, Pit *next, Pit *opposite, int seeds)
      : seeds_(seeds), next_(next), opposite_(opposite),
        label_(player->code + std::to_string(id)), owner_(player) {}
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

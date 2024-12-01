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
  Player *owner_;
  bool isStore();

public:
  Pit();
  Pit(Player *owner, int id, Pit *next, Pit *opposite,
      int seeds, int maxSeeds);
  ~Pit() = default;

  int grab();
  void drop(int n);
  int captureOpposite(Side side);

  bool isOppositeStore(Side side);
  bool isSameStore(Side side);

  Pit *getNext();
  int getSeeds();
  std::string getLabel();

  ostream &print(ostream &out) const;
};

inline ostream &operator<<(ostream &out, const Pit &p) {
  return p.print(out);
}

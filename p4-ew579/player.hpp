/*
 * Pit.hpp
 *
 *  Created on: Nov 7, 2024
 *      Author: Eric Wang
 */

#pragma once
#include <string>
using namespace std;

enum Side {
  South = 0,
  North = 1,
};

struct Player {
  Side side;
  string name;
  string code;

  Side otherSide() {
    return side == Side::South ? Side::North : Side::South;
  }
};

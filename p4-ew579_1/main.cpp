/*
 * Mancala-1
 * main.cpp
 *
 *  Created on: Oct 17, 2016; October 28, 2024
 *      Author: mike
 */

#include "game.hpp"
#include "tools.hpp"

static string usage = "usage: kalah numHouses numSeeds";

//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::cout << "Welcome to Kalah!" << std::endl;

  if (argc != 3)
    fatal(usage);
  int numHouses = atoi(argv[1]);
  int numSeeds = atoi(argv[2]);

  Game game(numHouses, numSeeds);
  game.playGame();
}

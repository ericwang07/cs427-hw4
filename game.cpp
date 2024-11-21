#include "game.hpp"
#include "kalah.cpp"
#include "outcome.hpp"
#include <ostream>

void Game::printInfo() {
  cout << "\n----------" << std::endl;
  cout << kalah_.getCurrPlayer() << "'s turn:" << std::endl;
  kalah_.showBoard();
  std::cout << "Please enter a pit number for " << kalah_.getCurrPlayer()
            << " (q to quit): ";
}

bool Game::askValidMove(int &move) {
  while (true) {
    std::cin >> move;

    if (!std::cin.fail() && kalah_.isValidMove(move)) {
      return true;
    }

    if (std::cin.eof()) { // eof check
      return false;
    };

    if (std::cin.fail()) {
      std::cin.clear();
      string command;
      std::cin >> command;
      if (command == "q") {
        std::cout << std::endl;
        std::cout << "Quitting game at user's request" << std::endl;
        std::cout << "Game over -- goodbye!" << std::endl;
        return false;
      }
    }

    std::cout << "Bad input -- please try again" << std::endl;
  }
  return true;
}

void Game::executeMove(int move) {
  std::cout << std::endl;
  std::cout << kalah_.getCurrPlayer() << " playing move " << move << std::endl;

  kalah_.doMove(move);
}

void Game::finishGame() {
  kalah_.endGame();

  cout << "\n----------" << std::endl;
  cout << "Game finished:" << std::endl;
  kalah_.showBoard();
  // announce final results
  Outcome outcome = kalah_.getOutcome();

  if (outcome == Outcome::NorthWin) {
    std::cout << "North won!" << std::endl;
  } else if (outcome == Outcome::SouthWin) {
    std::cout << "South won!" << std::endl;
  } else {
    std::cout << "North and South tied!" << std::endl;
  }

  std::cout << "North Total: " << kalah_.getNorthSeeds() << " seeds"
            << std::endl;
  std::cout << "South Total: " << kalah_.getSouthSeeds() << " seeds"
            << std::endl;

  std::cout << "Game over -- goodbye!" << std::endl;
}

void Game::playGame() {
  while (!std::cin.eof()) {

    printInfo();

    int move;

    if (!askValidMove(move)) {
      return;
    };

    executeMove(move);

    if (kalah_.isOver()) {
      finishGame();
      return;
    }

    if (kalah_.getAnotherTurn()) {
      std::cout << kalah_.getCurrPlayer() << " gets another turn" << std::endl;
      continue;
    }

    if (kalah_.getWasCaptured() && kalah_.getSeedsCaptured() > 0) {
      std::cout << "Captured " << kalah_.getSeedsCaptured() << " seeds"
                << std::endl;
    }

    std::cout << "Turn is over" << std::endl;
  }
}

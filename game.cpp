#include "game.hpp"
#include "kalah.cpp"
#include "outcome.hpp"
#include <ostream>

void Game::playGame() {
  while (true) { // NOTE: bad style
    displayBoard();

    std::cout << "Please enter a pit number for " << kalah_.getCurrPlayer()
              << " (q to quit): ";

    int move;
    std::cin >> move;

    if (std::cin.eof()) { // eof check
      return;
    };

    while (std::cin.fail() || !kalah_.isValidMove(move)) {

      if (std::cin.eof()) { // eof check
        return;
      };

      if (std::cin.fail()) {
        std::cin.clear();
        string command;
        std::cin >> command;
        if (command == "q") {
          std::cout << std::endl;
          std::cout << "Quitting game at user's request" << std::endl;
          std::cout << "Game over -- goodbye!" << std::endl;
          return;
        }
      }

      std::cout << "Bad input -- please try again" << std::endl;
      std::cin >> move;
    }

    std::cout << std::endl;
    std::cout << kalah_.getCurrPlayer() << " playing move " << move
              << std::endl;

    kalah_.doMove(move);

    if (kalah_.getAnotherTurn()) {
      std::cout << kalah_.getCurrPlayer() << " gets another turn" << std::endl;
      continue;
    }

    if (kalah_.getWasCaptured() && kalah_.getSeedsCaptured() > 0) {
      std::cout << "Captured " << kalah_.getSeedsCaptured() << " seeds"
                << std::endl;
    }

    std::cout << "Turn is over" << std::endl;

    if (kalah_.isOver()) {
      kalah_.endGame();

      // announce final results
      Outcome outcome = kalah_.getOutcome();

      if (outcome == Outcome::NorthWin) {
        std::cout << "North won!" << std::endl;
      } else if (outcome == Outcome::SouthWin) {
        std::cout << "South won!" << std::endl;
      } else {
        std::cout << "North and South tied!" << std::endl;
      }

      std::cout << "North captured " << kalah_.getNorthSeeds() << " seeds"
                << std::endl;
      std::cout << "South captured " << kalah_.getSouthSeeds() << " seeds"
                << std::endl;

      std::cout << "Game over -- goodbye!" << std::endl;
      return;
    }
  }
}

void Game::displayBoard() {
  cout << "\n----------" << std::endl;
  cout << kalah_.getCurrPlayer() << "'s turn:" << std::endl;
  kalah_.showBoard();
}

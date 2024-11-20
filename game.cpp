#include "game.hpp"
#include "kalah.cpp"

void Game::playGame() {
  while (!kalah_.isOver()) {
    displayBoard();

    int move;

    std::cout << "Please enter a pit number for " << kalah_.getCurrPlayer()
              << " (q to quit): ";
    std::cin >> move;
    std ::cout << std::endl;
    if (std::cin.eof()) {
      return;
    };
    if (!std::cin.fail()) {
      if (move <= maxMove_) {
        std::cout << kalah_.getCurrPlayer() << " playing move " << move
                  << std::endl;
        kalah_.doMove(move);
        bool anotherTurn = kalah_.getAnotherTurn();
        bool wasCaptured = kalah_.getWasCaptured();
        int seedsCaptured = kalah_.getSeedsCaptured();
        if (anotherTurn) {
          std::cout << kalah_.getCurrPlayer() << " gets another turn"
                    << std::endl;
        } else {
          if (wasCaptured && seedsCaptured > 0) {
            std::cout << "Captured " << seedsCaptured << " seeds" << std::endl;
          }
          std::cout << "Turn is over" << std::endl;
        }
      } else {
        // NOTE: try making this more specific (list all options)
        std::cout << "Invalid move. Please try again." << std::endl;
        continue;
      }
    } else {
      std::cin.clear();
      string command;
      std::cin >> command;
      if (command == "q") {
        std::cout << "Quitting game at user's request" << std::endl;
        return;
      } else {
        // NOTE: try making this more specific (list all options)
        std::cout << "Invalid move. Please try again." << std::endl;
        continue;
      }
    }
  }
}

void Game::displayBoard() {
  cout << "\n----------" << std::endl;
  cout << kalah_.getCurrPlayer() << "'s turn:" << std::endl;
  kalah_.showBoard();
}

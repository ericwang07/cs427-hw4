/*
 * UnitTest.hpp
 *
 *  Created on: Oct 29, 2016
 *      Author: mike
 */

#ifndef UNITTEST_HPP_
#define UNITTEST_HPP_

#include "board.cpp"

class UnitTest {
private:
  const Board bd;

public:
  UnitTest(int numHouses, int numSeeds)
      : bd(numHouses, numSeeds) {
    cout << "UnitTest constructor called" << endl;
  }
  ~UnitTest() = default;

  void run() const;
};

#endif /* UNITTEST_HPP_ */

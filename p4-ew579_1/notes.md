# Things to note:
## game.cpp
1. The askValidMove() function includes a second loop to keep prompting users until the move they input is valid.
## kalah.cpp
1. Kalah holds onto a maxMove member (numHouses) to help make move validation occur within Kalah (not Board).
2. Kalah updates a series of internal data members to track key states. These include:
    a. anotherTurn: boolean for if the curr player gets another turn. Part of tuurn state.
    b. seedsCaptured: number of seeds captured during most recent move. The specification says that there should be a
    boolean flag for whether the msot recent move ended in a capture, but this meaning is encoded into seedsCaptured 
    (value of 0). Part of turn state.
    c. northSeeds: final number of seeds captured in the north player's store. Part of game result state.
    d. southSeeds: final number of seeds captured in the south player's store. Part of game result state.
    e. outcome: The final outcome of the game: SouthWin, NorthWin, or Tie.
## board.cpp
1. sowAndCapture() returns an integer value. This integer encodes the result of the move.
    a. If it returns a non-zero positive integer, there was a successful capture. The number is the # of seeds gained.
    b. If it returns 0, there was no capture.
    c. If it returns a negative integer, the last stone to be sowed landed in curr player's store. Another turn is granted.

## Tests
I implemented 3 additional tests testing the following situations:
1. sample5: A full game with a tie outcome.
2. sample6: A full game with a South victory.
2. sample7: A full game with a North victory.
All tests have a corresponding input/output file pair.

I have also attached a testing shell script that runs all 7 tests simultaneously and diffs them with the expected
output simultaneously. It is called test_kalah.sh. Try running it with ./test_kalah.sh numHouses numSeeds.







#-----------------------------------------------------------
# Macro definitions
CXXFLAGS = -O1 -g -Wall -std=c++20
OBJ = main.o
TARGET = kalah
#-----------------------------------------------------------
# Rules
all: kalah

$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
#-----------------------------------------------------------
# Dependencies
main.o: main.cpp kalah.hpp kalah.cpp game.hpp game.cpp board.cpp board.hpp pit.hpp player.hpp tools.cpp tools.hpp outcome.hpp

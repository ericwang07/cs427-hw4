#-----------------------------------------------------------
# Macro definitions
CXXFLAGS = -O1 -g -Wall -std=c++20
OBJ = main.o
TARGET = frametest
#-----------------------------------------------------------
# Rules
all: frametest

$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
#-----------------------------------------------------------
# Dependencies
main.o: main.cpp kalah.hpp game.hpp board.cpp board.hpp pit.hpp player.hpp tools.cpp tools.hpp

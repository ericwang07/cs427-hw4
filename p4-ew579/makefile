CXX = c++
CXXFLAGS = -O1 -g -Wall -std=c++20

SOURCES = main.cpp game.cpp kalah.cpp board.cpp pit.cpp tools.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = kalah

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

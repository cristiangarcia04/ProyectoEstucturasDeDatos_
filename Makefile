CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = detective_game
SOURCES = main.cpp entidades/*.cpp datos/*.cpp juego/*.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

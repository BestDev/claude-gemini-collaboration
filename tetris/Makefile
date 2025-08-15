CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lncurses

TARGET = tetris

SRCS = src/main.cpp src/board.cpp src/piece.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o bin/$(TARGET) $(OBJS) $(LDFLAGS)

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

src/board.o: src/board.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

src/piece.o: src/piece.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f bin/$(TARGET) $(OBJS)
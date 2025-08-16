# Makefile for Tetris Game with multiple targets (v2)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# --- Directories ---
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# --- Ncurses Version ---
NCURSES_TARGET = tetris_ncurses
NCURSES_SRCS = $(SRC_DIR)/main_ncurses.cpp $(SRC_DIR)/board.cpp $(SRC_DIR)/piece.cpp
NCURSES_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(NCURSES_SRCS))
LDFLAGS = -lncurses

# --- Console Version ---
CONSOLE_TARGET = tetris_console
CONSOLE_SRCS = $(SRC_DIR)/main_console.cpp $(SRC_DIR)/board_console.cpp $(SRC_DIR)/piece.cpp
CONSOLE_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CONSOLE_SRCS))

# --- Default Target ---
all: ncurses

# --- Build Targets ---
ncurses: $(BIN_DIR)/$(NCURSES_TARGET)
console: $(BIN_DIR)/$(CONSOLE_TARGET)

$(BIN_DIR)/$(NCURSES_TARGET): $(NCURSES_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/$(CONSOLE_TARGET): $(CONSOLE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- Generic rule for object files ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all ncurses console clean

CXX      := g++
CXXFLAGS := -Wall -O3
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := build
PACKAGE := `pkg-config --cflags --libs gtk+-3.0`
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := sudoku_solver
INCLUDE  := -Iinclude/
SRC      :=\
	$(wildcard src/lib/*.cpp)\
	$(wildcard src/*.cpp)\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< $(PACKAGE)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(PACKAGE)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf build/*

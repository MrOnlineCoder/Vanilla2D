# Vanilla2D Makefile
# By MrOnlineCoder
# -----------------------------------------------------------
# PLEASE NOTE: Vanilla2D was originally made for(on) Windows, 
# this version Makefile does NOT guarantee successfull build on Linux
# Any help on contributing cross platform support is welcomed
# -----------------------------------------------------------

OS = $(shell uname)

# Files to compile
SRC_PRIMARY = Main.cpp Game.cpp Engine.cpp Script.cpp
SRC_SECONDARY = Utils.cpp Logger.cpp FPS.cpp Config.cpp ConfigParser.cpp

# Used C++ standard
STD=-std=c++11

# Executable filename
BIN=v2de

# Linker options
LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

# SFML includes folder path
SFML_INCLUDE_PATH=

# SFML libs folder path
SFML_LIBS_PATH=

all:
ifeq ($(OS), Linux)
	g++ $(STD) $(LIBS) $(SRC_PRIMARY) $(SRC_SECONDARY) -o $(BIN)
else
	g++ $(STD) -I"$(SFML_INCLUDE_PATH)" -L"$(SFML_LIBS_PATH)" $(SRC_PRIMARY) $(SRC_SECONDARY) -o $(BIN)
endif

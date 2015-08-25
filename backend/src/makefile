# Macros ========================================

CC=g++
CFLAGS=-c -g -Wall -ansi -pedantic -Wextra -Wno-unused-variable

ERASE=rm
OBJECTS=$(DIR)DDBInterface.o $(DIR)main.o
DIR=gnu/
EXE=$(DIR)Ladybug.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) -lcurl

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp

$(DIR)DDBInterface.o : DDBInterface.cpp DDBInterface.h
	$(CC) -o $(DIR)DDBInterface.o $(CFLAGS) DDBInterface.cpp
  
clean :
	$(ERASE) $(EXE) $(OBJECTS)
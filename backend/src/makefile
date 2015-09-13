# Macros ========================================

CC=g++
CFLAGS=-c -g -Wall -ansi -pedantic -Wextra

ERASE=rm
OBJECTS=$(DIR)DDBInterface.o $(DIR)main.o
DIR=gnu/
EXE=$(DIR)Ladybug.exe

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) -o Ladybug -lcurl

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp

$(DIR)DDBInterface.o : DDBInterface.cpp DDBInterface.h
	$(CC) -o $(DIR)DDBInterface.o $(CFLAGS) DDBInterface.cpp
  
clean :
	$(ERASE) $(EXE) $(OBJECTS)
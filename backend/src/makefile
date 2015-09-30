# Macros ========================================

CC=g++
CFLAGS=-c -g -Wall -ansi -pedantic -Wextra

ERASE=rm
OBJECTS= $(DIR)main.o
DIR=gnu/
EXE=$(DIR)Ladybug

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) -o Ladybug -lcurl

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp
  
clean :
	$(ERASE) $(EXE) $(OBJECTS)
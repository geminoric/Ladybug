# Macros ========================================

CC=g++-4.9
CFLAGS=-c -g 
ERASE=rm
OBJECTS= $(DIR)main.o $(DIR)aws4c.o
DIR=gnu/
EXE=$(DIR)Ladybug

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) -o Ladybug -lcurl -std=c++0x -lssl -lcrypto -Wno-write-strings

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp

$(DIR)aws4c.o : aws4c.c
	gcc -o $(DIR)aws4c.o $(CFLAGS) aws4c.c
  
clean :
	$(ERASE) $(EXE) $(OBJECTS)
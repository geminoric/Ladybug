# Macros ========================================

CC=g++-4.9
CFLAGS=-c -g 
ERASE=rm
OBJECTS= $(DIR)main.o $(DIR)aws4c.o $(DIR)ladybuguser.o $(DIR)ladybugusersconn.o $(DIR)ladybugobjects.o $(DIR)sha1.o
DIR=gnu/
EXE=$(DIR)Ladybug

# Targets ========================================

$(EXE) : $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) -o Ladybug -lcurl -std=c++0x -lssl -lcrypto -lonion

$(DIR)main.o : main.cpp
	$(CC) -o $(DIR)main.o $(CFLAGS) main.cpp

$(DIR)ladybuguser.o : ladybuguser.cpp ladybuguser.h
	$(CC) -o $(DIR)ladybuguser.o $(CFLAGS) ladybuguser.cpp

$(DIR)ladybugusersconn.o : ladybugusersconn.cpp ladybugusersconn.h
	$(CC) -o $(DIR)ladybugusersconn.o $(CFLAGS) ladybugusersconn.cpp

$(DIR)sha1.o : sha1.cpp sha1.h
	$(CC) -o $(DIR)sha1.o $(CFLAGS) sha1.cpp

$(DIR)ladybugobjects.o : ladybugobjects.cpp ladybugobjects.h
	$(CC) -o $(DIR)ladybugobjects.o $(CFLAGS) ladybugobjects.cpp

$(DIR)aws4c.o : aws4c.c
	gcc -o $(DIR)aws4c.o $(CFLAGS) aws4c.c
  
clean :
	$(ERASE) $(EXE) $(OBJECTS)
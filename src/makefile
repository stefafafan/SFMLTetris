CC=g++ -std=c++1y
CFLAGS=-c -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Entity.hpp Block.cpp Helpers.cpp Globals.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sfml

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
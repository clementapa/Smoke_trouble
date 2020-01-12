EXEC=smoke
SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
CCFLAGS=-Wall `sdl-config --cflags`
CC=g++
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -lSDL2 -lSDL2_ttf -lSDL2_image `sdl-config --libs` -o $(EXEC)
%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXEC)

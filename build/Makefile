CC=g++
CFLAGS=-std=c++11 -Wall -Wextra
LIBS=-lGL -lGLEW -lglfw

OBJS=*.o
EXE_NAME=visualizer.elf

all:
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(EXE_NAME)

run: $(EXE_NAME)
	./$(EXE_NAME)

clean:
	rm *

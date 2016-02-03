CC=g++
INCLUDE=../engine
CFLAGS=-std=c++11 -Wall -Wextra -I$(INCLUDE)
GENERATOR_SRC=generator.cpp
SIMULATOR_SRC=simulator.cpp

all:
	$(CC) $(CFLAGS) $(GENERATOR_SRC) -c
	$(CC) $(CFLAGS) $(SIMULATOR_SRC) -c

clean:
	rm *.o

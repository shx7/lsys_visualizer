CC=g++
INCLUDE=../engine
CFLAGS=-std=c++11 -Wall -Wextra -I$(INCLUDE) -ggdb
GENERATOR_SRC=generator.cpp
SIMULATOR_SRC=simulator.cpp
SYMBOL_BUILDER_SRC=symbol_builder.cpp

all: generator simulator symbol_builder

generator:
	$(CC) $(CFLAGS) $(GENERATOR_SRC) -c

simulator:
	$(CC) $(CFLAGS) $(SIMULATOR_SRC) -c

symbol_builder:
	$(CC) $(CFLAGS) $(SYMBOL_BUILDER_SRC) -c

clean:
	rm *.o

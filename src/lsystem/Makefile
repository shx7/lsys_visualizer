CC=g++
INCLUDE=../engine
CFLAGS=-std=c++11 -Wall -Wextra -I$(INCLUDE) -ggdb
GENERATOR_SRC=generator.cpp
SIMULATOR_SRC=simulator.cpp
SYMBOL_BUILDER_SRC=symbol_builder.cpp
RANDOM_GENERATOR_SRC=random_generator.cpp
PRODUCTION_SRC=production.cpp

all: generator simulator symbol_builder random_generator production

generator:
	$(CC) $(CFLAGS) $(GENERATOR_SRC) -c

simulator:
	$(CC) $(CFLAGS) $(SIMULATOR_SRC) -c

symbol_builder:
	$(CC) $(CFLAGS) $(SYMBOL_BUILDER_SRC) -c

random_generator:
	$(CC) $(CFLAGS) $(RANDOM_GENERATOR_SRC) -c

production:
	$(CC) $(CFLAGS) $(PRODUCTION_SRC) -c

clean:
	rm *.o

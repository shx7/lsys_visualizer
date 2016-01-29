CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

ENGINE_DIR=engine
SIMULATOR_DIR=simulator

all: engine simulator

simulator:
	$(MAKE) -C $(SIMULATOR_DIR)

engine:
	$(MAKE) -C $(ENGINE_DIR)

run:
	$(MAKE) -C .. run

.PHONY: engine simulator

clean:
	$(MAKE) -C .. clean

CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

ENGINE_DIR=engine
SRC=main.cpp
BUILD_DIR=../build

EXE_NAME=visualizer.elf

all: engine main
	$(MAKE) -C $(BUILD_DIR)

main:
	$(CC) $(CFLAGS) $(SRC) -c
	mv *.o $(BUILD_DIR)

engine:
	$(MAKE) -C $(ENGINE_DIR)
	mv $(ENGINE_DIR)//*.o $(BUILD_DIR)

.PHONY: engine 

clean:
	find $(BUILD_DIR) -name "*.o" -exec rm {} \;

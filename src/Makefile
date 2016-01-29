CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

ENGINE_DIR=engine
SIMULATOR_DIR=simulator
BUILD_DIR=../build

all: engine simulator
	$(MAKE) -C $(BUILD_DIR)

simulator:
	$(MAKE) -C $(SIMULATOR_DIR)
	mv $(SIMULATOR_DIR)/*.o $(BUILD_DIR)

engine:
	$(MAKE) -C $(ENGINE_DIR)
	mv $(ENGINE_DIR)/*.o $(BUILD_DIR)

run:
	$(MAKE) -C $(BUILD_DIR) run

.PHONY: engine simulator

clean:
	find $(BUILD_DIR) -name "*.o" -exec rm {} \;
	find $(BUILD_DIR) -name "*.elf" -exec rm {} \;

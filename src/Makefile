CC=g++
CFLAGS=-std=c++11 -Wall -Wextra

ENGINE_DIR=engine
SIMULATOR_DIR=simulator
LSYSTEM_DIR=lsystem
SHADERS_DIR=shaders
BUILD_DIR=../build

all: engine simulator lsystem update_shaders
	$(MAKE) -C .. collect_objs
	$(MAKE) -C .. link_objs

simulator:
	$(MAKE) -C $(SIMULATOR_DIR)

engine:
	$(MAKE) -C $(ENGINE_DIR)

lsystem:
	$(MAKE) -C $(LSYSTEM_DIR)

update_shaders:
	find $(SHADERS_DIR) -name "*.*" -exec cp {} $(BUILD_DIR) \;

run:
	$(MAKE) -C .. run

.PHONY: engine simulator lsystem

clean:
	$(MAKE) -C .. clean

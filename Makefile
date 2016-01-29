CC=g++
SRC_DIR=src
BUILD_DIR=build

all:
	$(MAKE) -C $(SRC_DIR)

collect_objs:
	find $(SRC_DIR) -name "*.o" -exec mv {} $(BUILD_DIR) \; 

link_objs:
	$(MAKE) -C $(BUILD_DIR)

run:
	$(MAKE) -C $(BUILD_DIR) run

clean:
	find $(BUILD_DIR) -name "*.o" -exec rm {} \;
	find $(BUILD_DIR) -name "*.elf" -exec rm {} \;

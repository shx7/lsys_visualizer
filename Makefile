CC=g++
SRC_DIR=src
BUILD_DIR=build

all:
	$(MAKE) -C $(SRC_DIR)
	find $(SRC_DIR) -name "*.o" -exec mv {} $(BUILD_DIR) \;
	$(MAKE) -C $(BUILD_DIR)

run:
	$(MAKE) -C $(BUILD_DIR) run

clean:
	find $(BUILD_DIR) -name "*.o" -exec rm {} \;
	find $(BUILD_DIR) -name "*.elf" -exec rm {} \;

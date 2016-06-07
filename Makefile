CC=g++
SRC_DIR=src
BUILD_DIR=build
SHADERS_DIR=$(SRC_DIR)/shaders
DOXYGEN_CONFIG=doxygen.config
DOC_DIR=doc

all: update_shaders collect_objs link_objs doc
	$(MAKE) -C $(SRC_DIR)

collect_objs:
	find $(SRC_DIR) -name "*.o" -exec mv {} $(BUILD_DIR) \; 

link_objs:
	$(MAKE) -C $(BUILD_DIR)

update_shaders:
	find $(SHADERS_DIR) -name "*.*" -exec cp {} $(BUILD_DIR) \;

run:
	$(MAKE) -C $(BUILD_DIR) run

doc:
	doxygen $(DOXYGEN_CONFIG)

clean:
	find $(BUILD_DIR) -name "*.o" -exec rm {} \;
	find $(BUILD_DIR) -name "*.elf" -exec rm {} \;
	rm $(DOC_DIR) -rf

.PHONY: doc

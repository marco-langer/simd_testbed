TARGET := simd.o

BUILD_DIR := build
OBJ_DIR := obj
SRC_DIR := src

.PHONY: all clean pre post

CXX := g++
CXXFLAGS := -c -g -std=c++20 -Wall -Wextra -Wpedantic -Werror -O2 -march=skylake-avx512 -ftree-vectorize
LDFLAGS := -g
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/$(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
DEPS := $(patsubst %.o, %.d, $(OBJ))
INCLUDES := -Iinclude

-include $(DEPS)

all: pre $(BUILD_DIR)/$(OBJ_DIR)/$(TARGET) post

pre:
	mkdir -p $(BUILD_DIR)/$(OBJ_DIR)

post:
	objdump -d $(BUILD_DIR)/$(OBJ_DIR)/$(TARGET) > $(BUILD_DIR)/dump.txt

clean:
	rm -rfv $(BUILD_DIR)

$(BUILD_DIR)/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(INCLUDES)

$(BUILD_DIR)/$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) -MM -MT "$@ $(patsubst %.d, %.o, $@)" -MF $@ $< $(INCLUDES)

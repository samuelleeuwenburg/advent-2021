CC = gcc
CFLAGS = -Wall -Werror -pedantic-errors -g
GDB = gdb
GDB_FLAGS = -q

SRC_DIR=src
BUILD_DIR=build

# INCLUDES=-I$(SRC_DIR)/helpers.h
# SRCS=$(SRC_DIR)/helpers.c

BINS = day01.elf day02.elf day03.elf day04.elf
TARGETS = $(patsubst %, $(BUILD_DIR)/%, $(BINS))

$(TARGETS): $(BUILD_DIR)%.elf:$(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(INCLUDES) $(CFLAGS) $(SRCS) $< -o $@

.PHONY: clean run all

all: $(TARGETS)

day=01
run: $(BUILD_DIR)/day$(day).elf
	$(BUILD_DIR)/day$(day).elf

debug: $(BUILD_DIR)/day$(day).elf
	$(GDB) $(GDB_FLAGS) $(BUILD_DIR)/day$(day).elf

clean:
	rm -rf ./build

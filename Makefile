#  output dir
OUTPUT_DIR = output
# output file name
TARGET = $(OUTPUT_DIR)/out
# compiler
CC = gcc

# compiler flags
CFLAGS = -Wall -Wextra -O2 -I$(INC_DIRS)

SRC_DIRS = src 
SRC_DIRS += lib/src

# source file
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# include directory
INC_DIRS = ./inc

build:
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

run: build
	./$(TARGET)

clear:
	rm -f $(TARGET)

.PHONY: build run clear

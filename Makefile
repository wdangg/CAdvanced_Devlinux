#  output dir
OUTPUT_DIR = output
# output file name
TARGET = $(OUTPUT_DIR)/out
# compiler
CC = gcc


SRC_DIRS = ./src 
SRC_DIRS += ./lib/src
SRC_DIRS += ./app

# source file
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# include directory
INC_DIRS = ./inc
INC_DIRS += ./app

# compiler flags
CFLAGS = -Wall -Wextra -O2 $(foreach dir,$(INC_DIRS),-I$(dir))

print-%:
	@echo "$* = $($*)"

build:
	@$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

run: build
	@./$(TARGET)

clear:
	@rm -f $(TARGET)

.PHONY: build run clear

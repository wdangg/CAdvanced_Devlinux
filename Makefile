# output file name
TARGET = out

# compiler
CC = gcc

# compiler flags
CFLAGS = -Wall -Wextra -O2

# source file
SRC = main.c

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clear:
	rm -f $(TARGET)

.PHONY: build run clear

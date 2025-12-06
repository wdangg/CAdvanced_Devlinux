RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

# project dir
PROJECT_DIR = .
#  output dir
OUTPUT_DIR = $(PROJECT_DIR)/output
# preprocessor dir
PRE_OUT_DIR = $(OUTPUT_DIR)/01_preprocessor
# compiler out dir
COM_OUT_DIR = $(OUTPUT_DIR)/02_compiler
# assembler out dir
ASS_OUT_DIR = $(OUTPUT_DIR)/03_assembler
# linker out dir
LINK_OUT_DIR = $(OUTPUT_DIR)/04_linker
# map out dir
MAP_OUT_DIR = $(OUTPUT_DIR)/map

# output file name
TARGET = $(OUTPUT_DIR)/out
# compiler
CC = gcc

SRC_DIRS = $(PROJECT_DIR)/src 
SRC_DIRS += $(PROJECT_DIR)/lib
SRC_DIRS += $(PROJECT_DIR)/app

# source file
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# include directory
INC_DIRS = $(PROJECT_DIR)/inc
INC_DIRS += $(PROJECT_DIR)/app
INC_DIRS += $(PROJECT_DIR)/lib

# compiler flags
CFLAGS = -Wall -Wextra -O2 $(foreach dir,$(INC_DIRS),-I$(dir)) -Wl,-Map=app.map

print-%:
	@echo "$* = $($*)"

preprocessor: $(patsubst %.c, %.i, $(SRC_FILES))
	@mkdir -p $(PRE_OUT_DIR)
	@echo "[STEP 1] preprocessing: *.c -> *.i"
	@$(CC) -E $< -o $(PRE_OUT_DIR)/$@
	@echo -e "$(GREEN)[MAKE_INFO] Preprocessing completed successfully!$(RESET)"

compiler:
	@mkdir -p $(COM_OUT_DIR)
	@echo "[STEP 2] compilling: *.i -> *.s"

assembler:
	@mkdir -p $(ASS_OUT_DIR)
	@echo "[STEP 3] assembling: *.s -> *.o"

linker:
	@mkdir -p $(LINK_OUT_DIR)
	@echo "[STEP 4] linking: *.o -> .exe"

build: preprocessor compiler assembler linker
# 	@$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)
	@echo -e "$(GREEN)[MAKE_INFO] Build completed successfully!$(RESET)"

run: build
	@./$(TARGET)

clear:
	@rm -f $(TARGET)

.PHONY: build run clear preprocessor compiler assembler linker

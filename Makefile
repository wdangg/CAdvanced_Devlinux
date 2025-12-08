RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[34m
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

# output file name
TARGET = out
# compiler
CC = gcc

SRC_DIRS = $(PROJECT_DIR)/src 
SRC_DIRS += $(PROJECT_DIR)/lib
SRC_DIRS += $(PROJECT_DIR)/app
SRC_DIRS += $(PROJECT_DIR)/Utils

# source file
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# include directory
INC_DIRS = $(PROJECT_DIR)/inc
INC_DIRS += $(PROJECT_DIR)/app
INC_DIRS += $(PROJECT_DIR)/lib
INC_DIRS += $(PROJECT_DIR)/Utils

# compiler flags
CFLAGS = -Wall -Wextra -O2 $(foreach dir,$(INC_DIRS),-I$(dir)) -Wl,-Map=$(TARGET).map

print-%:
	@echo "$* = $($*)"

PRE_I_FILES = $(patsubst %.c,$(PRE_OUT_DIR)/%.i,$(notdir $(SRC_FILES)))
COM_S_FILES = $(patsubst %.c,$(COM_OUT_DIR)/%.s,$(notdir $(SRC_FILES)))
ASS_O_FILES = $(patsubst %.s,$(ASS_OUT_DIR)/%.o,$(notdir $(COM_S_FILES)))

vpath %.c $(SRC_DIRS)
vpath %.i $(PRE_OUT_DIR)
vpath %.s $(COM_OUT_DIR)
vpath %.o $(ASS_OUT_DIR)

preprocessor: $(PRE_I_FILES)
	@echo -e "$(GREEN)[MAKE_INFO] Preprocessing completed successfully!$(RESET)"

$(PRE_OUT_DIR)/%.i: %.c
	@mkdir -p $(PRE_OUT_DIR)
	@echo "[PREPROCESSING] $< -> $@"
	@$(CC) -E $(foreach dir,$(INC_DIRS),-I$(dir)) $< -o $@

compiler: $(COM_S_FILES)
	@echo -e "$(GREEN)[MAKE_INFO] Compiling completed successfully!$(RESET)"

$(COM_OUT_DIR)/%.s: %.i
	@mkdir -p $(COM_OUT_DIR)
	@echo -e "[COMPILLING] $< -> $@"
	@$(CC) -S $(foreach dir,$(INC_DIRS),-I$(dir)) $< -o $@

assembler: $(ASS_O_FILES)
	@echo -e "$(GREEN)[MAKE_INFO] Assembling completed successfully!$(RESET)"

$(ASS_OUT_DIR)/%.o: %.s
	@mkdir -p $(ASS_OUT_DIR)
	@echo -e "[ASSEMBLING] $< -> $@"
	@$(CC) -c $(foreach dir,$(INC_DIRS),-I$(dir)) $< -o $@

linker:
	@mkdir -p $(LINK_OUT_DIR)
	@$(CC) $(ASS_O_FILES) -o $(LINK_OUT_DIR)/$(TARGET) -Wl,-Map=$(LINK_OUT_DIR)/$(TARGET).map

build: preprocessor compiler assembler linker
	@echo -e "$(GREEN)[MAKE_INFO] Build completed successfully!$(RESET)"

run:
	@./$(LINK_OUT_DIR)/$(TARGET).exe

all: clear build run

clear:
	@rm -rf $(OUTPUT_DIR)

.PHONY: build run clear preprocessor compiler assembler linker all

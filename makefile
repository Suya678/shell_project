CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./headers
BUILD_DIR = build
OBJ_DIR = build/obj_files
SRC_DIR = src
HEADERS_DIR = ./headers

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = $(BUILD_DIR)/jdshell





$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS_DIR)/*.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


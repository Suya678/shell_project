
CC = gcc
CFLAGS = -Wall -Wextra -I$(HDR_DIR)

SRC_DIR = ../../src
HDR_DIR = ../../headers
BUILD_DIR = .
OBJ_FILES = tst_cmd_runner.o our_string.o cmd_runner.o add_features.o error_handler.o

tst_cmd_runner: $(OBJ_FILES)
	$(CC) $(CFLAGS)  $^ -o $@

tst_cmd_runner.o: tst_cmd_runner.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

our_string.o: $(SRC_DIR)/our_string.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

cmd_runner.o: $(SRC_DIR)/cmd_runner.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

add_features.o: $(SRC_DIR)/add_features.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

error_handler.o: $(SRC_DIR)/error_handler.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

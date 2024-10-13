CC = gcc
CFLAGS = -Wall -Wextra -I$(HDR_DIR)

SRC_DIR = ../../src
HDR_DIR = ../../headers
BUILD_DIR = .
OBJ_FILES = tst_parser.o our_string.o parser.o error_handler.o

tst_parser: $(OBJ_FILES)
	$(CC) $(CFLAGS)  $^ -o $@

tst_parser.o: tst_parser.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

our_string.o: $(SRC_DIR)/our_string.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

parser.o: $(SRC_DIR)/parser.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

error_handler.o: $(SRC_DIR)/error_handler.c $(HDR_DIR)/*
	$(CC) $(CFLAGS) -c $< -o $@

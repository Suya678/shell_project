
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./headers

BUILD_DIR = build
OBJ_DIR = build/obj_files
SRC_DIR = src
HEADERS_DIR = headers
ALL_HDRS = headers/*.h
TARGET = $(BUILD_DIR)/quantum_shell

OBJ_FILES = $(OBJ_DIR)/quantum_shell.o $(OBJ_DIR)/add_features.o $(OBJ_DIR)/cmd_runner.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/error_handler.o $(OBJ_DIR)/our_string.o

all: $(TARGET)



$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/quantum_shell.o: $(SRC_DIR)/quant_shell.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/add_features.o: $(SRC_DIR)/add_features.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/cmd_runner.o: $(SRC_DIR)/cmd_runner.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/error_handler.o: $(SRC_DIR)/error_handler.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/our_string.o: $(SRC_DIR)/our_string.c $(ALL_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)


clean:
	rm $(TARGET) $(OBJ_DIR)/*.o
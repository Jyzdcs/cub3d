# Makefile for cub3d unit tests

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
ROOT_DIR = ..
SRC_DIR = $(ROOT_DIR)/src
INCLUDE_DIR = $(ROOT_DIR)/include
TESTS_DIR = .
UNITY_DIR = $(TESTS_DIR)/Unity/src
LIBS_DIR = $(ROOT_DIR)/libs
LIBFT_DIR = $(LIBS_DIR)/libft

# Source files
SRC_FILES = $(SRC_DIR)/map_parser/file_check.c \
						$(SRC_DIR)/map_parser/map_is_closed.c \
						$(SRC_DIR)/controls_handler/keys_input.c
# Add more source files as needed

# Test files
TEST_FILES = $(shell find $(TESTS_DIR)/tests -name "*.c")

# Unity files
UNITY_FILES = $(UNITY_DIR)/unity.c

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Include directories
INCLUDES = -I$(INCLUDE_DIR) -I$(UNITY_DIR) -I$(LIBFT_DIR)

# Object files
TEST_OBJECTS = $(TEST_FILES:.c=.o)

# Executables - extract just the base name without the directory
TEST_EXECUTABLES = $(notdir $(basename $(TEST_FILES)))

# Phony targets
.PHONY: all clean fclean re run run_single

# Default target
all: $(TEST_EXECUTABLES)

# Rule for test executables
$(TESTS_DIR)/tests/%.o: $(TESTS_DIR)/tests/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%: tests/%.o $(UNITY_FILES:.c=.o) $(SRC_FILES:.c=.o) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

# Compile Unity source
$(UNITY_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile project source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft if needed
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Run all tests
run: all
	@echo "Running all tests..."
	@for test in $(TEST_EXECUTABLES); do \
		echo "\n--- Running $$test ---"; \
		./$$test; \
		if [ $$? -ne 0 ]; then \
			echo "Test $$test failed!"; \
			exit 1; \
		fi; \
	done
	@echo "\nAll tests passed successfully!"

# Run a single test (usage: make run_single TEST=test_name)
run_single: all
	@if [ -z "$(TEST)" ]; then \
		echo "ERROR: Test name not specified. Usage: make run_single TEST=test_name"; \
		exit 1; \
	fi
	@if [ ! -f "./$(TEST)" ]; then \
		echo "ERROR: Test '$(TEST)' does not exist"; \
		exit 1; \
	fi
	@echo "\n--- Running $(TEST) ---"
	@./$(TEST)

# Clean object files
clean:
	$(RM) $(TEST_OBJECTS) $(UNITY_FILES:.c=.o) $(SRC_FILES:.c=.o)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean all generated files
fclean: clean
	$(RM) $(TEST_EXECUTABLES)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild all
re: fclean all

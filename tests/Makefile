# Makefile for cub3d unit tests

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -DUNITY_INCLUDE_DOUBLE -DTESTING
MLX_FLAGS = -framework OpenGL -framework AppKit
XQUARTZ_LIB = /opt/X11/lib
XQUARTZ_INCLUDE = /opt/X11/include
LDFLAGS = -lm -L$(MLX_DIR) -lmlx -L$(XQUARTZ_LIB) -lXext -lX11 $(MLX_FLAGS)

# Directories
ROOT_DIR = ..
SRC_DIR = $(ROOT_DIR)/src
INCLUDE_DIR = $(ROOT_DIR)/include
TESTS_DIR = .
UNITY_DIR = $(TESTS_DIR)/Unity/src
LIBS_DIR = $(ROOT_DIR)/libs
LIBFT_DIR = $(LIBS_DIR)/libft
MLX_DIR = $(LIBS_DIR)/minilibx_opengl_20191021

# Source files
SRC_FILES = $(SRC_DIR)/map_parser/check_extension.c \
						$(SRC_DIR)/map_parser/map_is_closed.c \
						$(SRC_DIR)/map_parser/file_content_check.c \
						$(SRC_DIR)/map_parser/file_content_utils.c \
						$(SRC_DIR)/map_parser/file_content_map_at_the_end.c \
						$(SRC_DIR)/utils/game_cleaner.c \
						$(SRC_DIR)/utils/map_copy.c \
						$(SRC_DIR)/main.c \
						$(SRC_DIR)/controls_handler/keys_input.c \
						$(SRC_DIR)/controls_handler/keys_movement.c \
						$(SRC_DIR)/controls_handler/keys_camera_rotation.c \
						$(SRC_DIR)/map_parser/map_have_one_player.c \
						$(SRC_DIR)/map_parser/map_checker.c \
						$(SRC_DIR)/raycasting/raycasting_init.c \
						$(SRC_DIR)/raycasting/ray_casting.c \
						$(SRC_DIR)/map_parser/textures_checker.c \
						$(SRC_DIR)/map_parser/rgb_checker.c \
						$(SRC_DIR)/utils/array_utils.c \
					$(SRC_DIR)/rendering/init_game_textures.c \
					$(SRC_DIR)/rendering/init_game_rgb.c \
					$(SRC_DIR)/rendering/init_player_data.c \
					$(SRC_DIR)/rendering/rendering.c \
					$(SRC_DIR)/rendering/render_floor_and_ceiling.c \
					$(SRC_DIR)/rendering/rendering_utils.c
# Note: main.c is excluded because test files define their own main function
# Add more source files as needed

# Test files
TEST_FILES = $(shell find $(TESTS_DIR)/tests -name "*.c")

# Unity files
UNITY_FILES = $(UNITY_DIR)/unity.c

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Include directories
INCLUDES = -I$(INCLUDE_DIR) -I$(UNITY_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(XQUARTZ_INCLUDE)

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

%: tests/%.o $(UNITY_FILES:.c=.o) $(SRC_FILES:.c=.o) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $< $(UNITY_FILES:.c=.o) $(SRC_FILES:.c=.o) $(LIBFT) $(MLX) -o $@ $(LDFLAGS)

# Compile Unity source
$(UNITY_DIR)/%.o: $(UNITY_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile project source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft if needed
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Build MiniLibX if needed
$(MLX):
	$(MAKE) -C $(MLX_DIR)

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
	$(MAKE) -C $(MLX_DIR) clean

# Clean all generated files
fclean: clean
	$(RM) $(TEST_EXECUTABLES)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild all
re: fclean all

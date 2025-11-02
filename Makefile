# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:00:00 by kclaudan          #+#    #+#              #
#    Updated: 2025/11/02 18:09:22 by kclaudan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Source directories and files
SRC_DIR = src
SRC_FILES = main.c \
			map_parser/check_extension.c \
			map_parser/map_is_closed.c \
			map_parser/map_checker.c \
			utils/file_content_check_utils.c \
			map_parser/rgb_and_textures_checker.c \
			map_parser/textures_checker.c \
			map_parser/rgb_checker.c \
			map_parser/file_content_check.c \
			map_parser/file_content_utils.c \
			map_parser/file_content_map_at_the_end.c \
			map_parser/map_have_one_player.c \
			utils/array_utils.c \
			utils/map_copy.c \
			utils/game_cleaner.c \
			rendering/rendering.c \
			rendering/render_floor_and_ceiling.c \
			rendering/rendering_utils.c \
			rendering/init_game_textures_and_colors.c \
			rendering/init_player_data.c \
			controls_handler/keys_input.c \
			controls_handler/keys_camera_rotation.c \
			controls_handler/keys_movement.c \
			raycasting/ray_casting.c \
			raycasting/raycasting_init.c \
# Create full paths for source files
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Libft library
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX library
# For Linux: Install Linux MiniLibX in minilibx/mlx directory
MLX_DIR = minilibx/mlx
# For macOS (uncomment if needed - uses Objective-C .m files):
# MLX_DIR = libs/minilibx_opengl_20191021
MLX = $(MLX_DIR)/libmlx.a

# XQuartz paths for macOS (comment out for Linux)
# XQUARTZ_INCLUDE = /opt/X11/include
# XQUARTZ_LIB = /opt/X11/lib

# Include paths
INCLUDES = -I ./include -I $(LIBFT_DIR) -I $(MLX_DIR)

# MLX linking flags
# For macOS with XQuartz/X11 (uncomment if needed):
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -L$(XQUARTZ_LIB) -lXext -lX11 -framework OpenGL -framework AppKit
# For Linux (X11 libs in standard system paths):
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

# Default target
all: $(NAME)

# Ensure obj directories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build MiniLibX
$(MLX):
	@make -C $(MLX_DIR)

# Build the executable
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "Linking $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -lm -o $(NAME)
	@echo "Build complete!"

# Clean object files
clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)

# Clean objects and binary
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

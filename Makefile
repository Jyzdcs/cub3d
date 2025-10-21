# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:00:00 by kclaudan          #+#    #+#              #
#    Updated: 2025/10/11 15:50:36 by kclaudan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# Source directories and files
SRC_DIR = src
SRC_FILES = main.c \
			map_parser/file_check.c \
			map_parser/file_content_check.c \
			map_parser/file_content_utils.c \
			map_parser/file_content_map_at_the_end.c \
			map_parser/map_is_closed.c \
			map_parser/map_have_one_player.c \
			utils/game_cleaner.c \
			rendering/rendering.c \
			rendering/rendering_utils.c \
			rendering/render_floor_and_ceiling.c \
			controls_handler/keys_input.c \
			raycasting/ray_casting.c \
			raycasting/raycasting_init.c

# Create full paths for source files
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Libft library
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX library
MLX_DIR = minilibx/mlx
MLX = $(MLX_DIR)/libmlx.a

# Include paths
INCLUDES = -I ./include -I $(LIBFT_DIR) -I $(MLX_DIR)

# MLX linking flags (for Linux/WSL2)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm

# Default target
all: $(NAME)

# Ensure obj directories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build MiniLibX
$(MLX):
	@make -C $(MLX_DIR)

# Build the executable
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

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

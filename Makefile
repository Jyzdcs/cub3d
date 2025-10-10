# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 12:00:00 by kclaudan          #+#    #+#              #
#    Updated: 2025/10/10 13:03:56 by kclaudan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source directories and files
SRC_DIR = src
SRC_FILES = main.c \
			map_parser/file_check.c map_parser/file_content_check.c utils/ressources_cleaner.c utils/game_cleaner.c map_parser/file_content_utils.c map_parser/file_content_map_at_the_end.c

# Create full paths for source files
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Libft library
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Include paths
INCLUDES = -I ./include -I $(LIBFT_DIR)

# Default target
all: $(NAME)

# Ensure obj directories exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build the executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Clean object files
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

# Clean objects and binary
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re

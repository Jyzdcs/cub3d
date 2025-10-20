/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:56:31 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/20 14:43:25 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include "cub3d.h"

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_game	t_game;

/* MAP HAVE ONE PLAYER */
int						map_have_one_player(char **map);

/* MAP IS CLOSED */
int						map_is_closed(char **map_copy, t_map *map,
							t_player *player);

/* FILE CHECK */
int						ft_check_extension(char *file_path, char *extension,
							int extension_len);
int						map_is_closed(char **map_copy, t_map *map,
							t_player *player);
int						file_handler(char *path, t_game *game);

/* FILE CONTENT UTILS */
int						ft_isspace(char c);
int						ft_comp(char *s1, char *s2);
int						ft_is_identifier(char *id);
int						ft_is_line_empty(char *line);
int						export_file(t_game *game, int fd, char *path);

/* FILE CONTENT MAP AT THE END */
int						ft_is_char_accepted_in_map(char c);
int						ft_start_index_of_the_map(char **file);
int						ft_end_index_of_the_map(char **file, int first_line);
int						ft_find_last_index(int index, char **file);
int						ft_map_is_at_the_end(char **file);

/* TEXTURES EXTENSION CHECKER */
int						ft_find_path_to_textures(char *line);
int						ft_is_valid_path(char *path);
int						ft_textures_checker(t_game *game);

/* RGB CHECKER */
int						ft_is_valid_rgb(char *rgb);
int						ft_index_of_first_rgb(char *line);
int						ft_rgb_checker(t_game *game);

/* MAP CHECKER */
int						map_is_valid(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:56:31 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/06 11:42:03 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "utils.h"

typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_game t_game;

int check_extension(char *path);
int map_is_closed(char **map_copy, t_map *map, t_player *player);
int file_handler(char *path, t_game *game);

#endif

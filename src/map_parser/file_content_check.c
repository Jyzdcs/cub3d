/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/06 15:08:38 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

int ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int ft_is_identifier(char *id)
{
	return (!ft_strncmp(id, "NO", 2) || !ft_strncmp(id, "SO", 2) ||
					!ft_strncmp(id, "WE", 2) || !ft_strncmp(id, "EA", 2) ||
					!ft_strncmp(id, "F", 1) || !ft_strncmp(id, "C", 1));
}

char **export_file_content(char *path)
{
	int fd;
	int i;
	char **line;
	char *buff;

	fd = open(path, O_RDONLY);
	i = 0;
	while (1)
	{
		buff = get_next_line(fd);
		i++;
		if (!buff)
			break;
		free(buff);
	}
	close(fd);
	line = malloc(sizeof(char *) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line[i++] = get_next_line(fd);
		if (!line[i])
			break;
	}
	close(fd);
	return (line);
}

int file_is_empty(char **file)
{
	int i;
	int j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (ft_isspace(file[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int ft_textures_handler(char **file, t_game *game)
{
	(void)file;
	(void)game;
	return (TRUE);
}

int ft_color_handler(char **file, t_game *game)
{
	(void)file;
	(void)game;
	return (TRUE);
}

/*
fonction qui check boucle jusquau premier char visible
si apres avoir skip les white space file[i][j] != un id valide
return FALSE
*/
int check_file_content(t_game *game)
{
	int i;
	int j;
	int id_counter = 0;

	i = 0;
	while (game->file[i])
	{
		j = 0;
		while (ft_isspace(game->file[i][j]) == TRUE)
			j++;
		if (ft_is_identifier(game->file[i]) == TRUE)
		{
			id_counter++;
			j += 3;
			// if (ft_doublon_detect(game->file, game) == TRUE)
			// 	exit_game(game, "Error: Map contain doublon");
			if (ft_color_handler(game->file, game) == TRUE || ft_textures_handler(game->file, game) == TRUE)
				;
		}
		else if (id_counter != 5)
			return (exit_game(game, "Error: Invalid Map format identifier missing\n")), FALSE;
		i++;
	}
	return (TRUE);
}

int parse_content(char *path, t_game *game)
{
	game->file = export_file_content(path);
	if (!game->file)
		return (FALSE);
	if (file_is_empty(game->file) == TRUE)
		return (FALSE);
	if (check_file_content(game) == TRUE)
		return (FALSE);
	return (TRUE);
}

// Return true si le content est bon
int file_handler(char *path, t_game *game)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: file doesnt exist\n", 2);
		return (FALSE);
	}
	if (parse_content(path, game) == FALSE)
		return (FALSE);
	close(fd);
	return (TRUE);
}
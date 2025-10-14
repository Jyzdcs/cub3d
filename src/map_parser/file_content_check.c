/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/14 13:24:03 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

int	ft_identifiers_register_check(char id[6])
{
	int	i;
	int	j;

	i = 0;
	while (id[i])
	{
		j = i + 1;
		while (id[j])
		{
			if (id[i] == id[j++])
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	count_file_line(char *path)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		i++;
		if (!str)
			break ;
		free(str);
	}
	close(fd);
	if (i == 1)
		return (0);
	return (i);
}

int	export_file(t_game *game, int fd, char *path)
{
	int	i;
	int	file_size;

	i = 0;
	file_size = count_file_line(path);
	if (file_size == 0)
		return (FALSE);
	game->file = malloc(sizeof(char *) * file_size);
	if (!game->file)
		return (exit_game(game, "Error allocation memory on file\n"), FALSE);
	while (i < file_size - 1)
	{
		game->file[i] = get_next_line(fd);
		if (!game->file[i])
		{
			free_all(game->file);
			close(fd);
			exit_game(game, "Error allocation memory on export file\n");
			return (FALSE);
		}
		i++;
	}
	game->file[i] = NULL;
	close(fd);
	return (TRUE);
}

int	structure_file_is_valid(t_game *game)
{
	int	i;
	int	id_counter;
	int	id_index;
	int	j;

	char id[7]; // Increased size to ensure space for null terminator
	i = 0;
	id_counter = 0;
	id_index = 0;
	ft_memset(id, 0, sizeof(id)); // Initialize array with zeros
	while (game->file[i])
	{
		j = 0;
		if (game->file[i] && ft_is_line_empty(game->file[i]) == TRUE)
			i++;
		else
		{
			if (ft_is_identifier(game->file[i]) > 0)
			{
				while (game->file[i][j] && ft_isspace(game->file[i][j]) == TRUE)
					j++;
				id[id_index++] = game->file[i][j];
				id_counter++;
			}
			else if (id_counter != 6 && ft_is_identifier(game->file[i]) == 0
				&& ft_is_line_empty(game->file[i]) == FALSE)
			{
				ft_putstr_fd("Error: invalid line before identifiers\n", 2);
				return (FALSE);
			}
			i++;
		}
	}
	if (ft_identifiers_register_check(id) == FALSE)
	{
		ft_putstr_fd("Error: identifier duplicate\n", 2);
		return (FALSE);
	}
	if (id_counter != 6)
	{
		ft_putstr_fd("Error: invalids number of identifier\n", 2);
		return (FALSE);
	}
	if (ft_map_is_at_the_end(game->file) == FALSE)
	{
		ft_putstr_fd("Error: map isnt at the end of the file\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

// Return true si le content est bon
int	file_handler(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: file doesnt exist\n", 2);
		return (FALSE);
	}
	if (export_file(game, fd, path) == FALSE)
	{
		close(fd);
		return (FALSE);
	}
	if (structure_file_is_valid(game) == FALSE)
	{
		free_all(game->file);
		close(fd);
		return (FALSE);
	}
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (TRUE);
}

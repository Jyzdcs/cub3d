/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/02 19:37:30 by kclaudan         ###   ########.fr       */
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
	if (fd < 0)
		return (close(fd),
			ft_putstr_fd("Error: file doesnt exist or permission denied\n", 2),
			FALSE);
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
		return (ft_putstr_fd("Error: file is empty\n", 2), FALSE);
	game->file = malloc(sizeof(char *) * file_size);
	if (!game->file)
		return (ft_putstr_fd("Error: allocation memory on file\n", 2), FALSE);
	while (i < file_size - 1)
	{
		game->file[i] = get_next_line(fd);
		if (!game->file[i])
			return (ft_putstr_fd("Error: allocation memory on export file\n",
					2), FALSE);
		i++;
	}
	game->file[i] = NULL;
	return (TRUE);
}
int	structure_file_is_valid(t_game *game)
{
	char	id[7];
	int		id_counter;

	id_counter = 0;
	ft_memset(id, 0, sizeof(id));
	if (collect_identifiers(game->file, id, &id_counter) == FALSE)
		return (ft_putstr_fd("Error: invalid line before identifiers\n", 2),
			FALSE);
	if (ft_identifiers_register_check(id) == FALSE)
		return (ft_putstr_fd("Error: identifier duplicate\n", 2), FALSE);
	if (id_counter != 6)
		return (ft_putstr_fd("Error: invalids number of identifier\n", 2),
			FALSE);
	if (ft_map_is_at_the_end(game->file) == FALSE)
		return (ft_putstr_fd("Error: map isnt at the end of the file\n", 2),
			FALSE);
	return (TRUE);
}

// Return true si le content est bon
int	file_handler(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: file doesnt exist or permission denied\n", 2);
		return (FALSE);
	}
	if (export_file(game, fd, path) == FALSE)
	{
		close(fd);
		exit_game(game, "Error: export file failed\n");
	}
	if (structure_file_is_valid(game) == FALSE)
	{
		close(fd);
		return (FALSE);
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/07 22:58:49 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

int ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int ft_comp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (s1[i] == s2[i] && (s1[i] && s2[i]))
		i++;
	if (!s2[i] && s1[i] == ' ')
		return (TRUE);
	return (FALSE);
}

int ft_is_line_empty(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) != TRUE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int identifiers_register_check(char id[6])
{
	int i;
	int j;

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

int ft_is_identifier(char *id)
{
	if (ft_comp(id, "NO") == TRUE || ft_comp(id, "SO") == TRUE ||
			ft_comp(id, "WE") == TRUE || ft_comp(id, "EA") == TRUE)
		return (1);
	else if (ft_comp(id, "F") == TRUE || ft_comp(id, "C") == TRUE)
		return (2);
	return (0);
}

void print_2d_array(char **arr)
{
	int i = 0;
	int j;

	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
			printf("%c", arr[i][j++]);
		printf("\n");
		i++;
	}
}

int count_file_line(char *path)
{
	int i;
	int fd;
	char *str;

	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		i++;
		if (!str)
			break;
		free(str);
	}
	close(fd);
	if (i == 1)
		return (0);
	return (i);
}

int export_file(t_game *game, int fd, char *path)
{
	int i;
	int file_size;

	i = 0;
	file_size = count_file_line(path);
	if (file_size == 0)
		return (exit_game(game, "Error: File is empty\n"), FALSE);
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

int structure_file_is_valid(t_game *game)
{
	int i;
	int id_counter;
	char id[6];
	// int id_type;
	int id_index;

	i = 0;
	id_counter = 0;
	id_index = 0;
	while (game->file[i])
	{
		// id_type = ft_is_identifier(game->file[i]);
		if (ft_is_identifier(game->file[i]) > 0)
		{
			id[id_index++] = game->file[i][0];
			id_counter++;
		}
		else if (id_counter != 6 && ft_is_identifier(game->file[i]) == 0 && ft_is_line_empty(game->file[i]) == FALSE)
		{
			ft_putstr_fd("Error: invalid line before identifiers\n", 2);
			return (FALSE);
		}
		i++;
	}
	if (identifiers_register_check(id) == FALSE)
	{
		ft_putstr_fd("Error: identifier duplicate\n", 2);
		return (FALSE);
	}
	if (id_counter != 6)
	{
		ft_putstr_fd("Error: invalids number of identifier\n", 2);
		return (FALSE);
	}
	// return (printf("numbers of id : %d\n", id_counter), exit_game(game, "Error: all identifers not found at the beginning of the file\n\n\n"), FALSE);
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
	if (export_file(game, fd, path) == FALSE)
		return (FALSE);
	if (structure_file_is_valid(game) == FALSE)
	{
		return (FALSE);
	}
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (TRUE);
}
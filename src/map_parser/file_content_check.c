/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/09 19:52:12 by kclaudan         ###   ########.fr       */
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
	int i;

	i = 0;
	while (id[i] != '\0' && id[i] == ' ')
		i++;
	if (id[i] == '\0')
		return (0);
	printf("%s\n", &id[i]);
	if (ft_comp(&id[i], "NO") == TRUE || ft_comp(&id[i], "SO") == TRUE || ft_comp(&id[i], "WE") == TRUE || ft_comp(&id[i], "EA") == TRUE)
		return (1);
	else if (ft_comp(&id[i], "F") == TRUE || ft_comp(&id[i], "C") == TRUE)
		return (2);
	return (0);
}

void print_2d_array(char **arr)
{
	int i;
	int j;

	i = 0;
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

int is_char_accepted_in_map(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (TRUE);
	return (FALSE);
}

int ft_start_index_of_the_map(char **file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (ft_is_identifier(file[i]) > 0 || ft_is_line_empty(file[i]) == TRUE)
			i++;
		else
			return (i);
	}
	return (-1);
}

int ft_end_index_of_the_map(char **file, int first_line)
{
	int i;

	i = first_line;
	while (file[i + 1] && ft_is_identifier(file[i + 1]) == 0 && ft_is_line_empty(file[i + 1]) == FALSE)
		i++;
	return (i);
}

int ft_find_last_index(int index, char **file)
{
	int i;

	i = index;
	while (file[i])
		i++;
	return (i);
}

int map_is_at_the_end(char **file)
{
	int start_of_the_map;
	int end_of_the_map;
	int end_of_file;
	int i;

	start_of_the_map = ft_start_index_of_the_map(file);
	if (start_of_the_map == -1)
		return (FALSE);
	end_of_the_map = ft_end_index_of_the_map(file, start_of_the_map);
	end_of_file = ft_find_last_index(end_of_the_map, file);
	if (end_of_file == end_of_the_map)
		return (TRUE);
	i = end_of_the_map + 1;
	while (file[i] && ft_is_line_empty(file[i]) == TRUE)
		i++;
	if (i == end_of_file)
		return (TRUE);
	return (FALSE);
}

int structure_file_is_valid(t_game *game)
{
	int i;
	int id_counter;
	char id[6];
	int id_index;
	int j;

	i = 0;
	id_counter = 0;
	id_index = 0;
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
			else if (id_counter != 6 && ft_is_identifier(game->file[i]) == 0 && ft_is_line_empty(game->file[i]) == FALSE)
			{
				ft_putstr_fd("Error: invalid line before identifiers\n", 2);
				return (FALSE);
			}
			i++;
		}
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
	if (map_is_at_the_end(game->file) == FALSE)
	{
		ft_putstr_fd("Error: map isnt at the end of the file\n", 2);
		return (FALSE);
	}
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
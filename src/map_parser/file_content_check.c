/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/07 14:08:11 by kclaudan         ###   ########.fr       */
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

int ft_comp(char *s1, char *s2, int n)
{
	int i;

	i = 0;
	if (n <= 0)
		return (FALSE);
	if (!s1 || !s2)
		return (FALSE);
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	if (i < n)
		return (FALSE);
	return (TRUE);
}

int ft_is_identifier(char *id)
{
	if (ft_comp(id, "NO", 2) == TRUE || ft_comp(id, "SO", 2) == TRUE ||
			ft_comp(id, "WE", 2) == TRUE || ft_comp(id, "EA", 2) == TRUE ||
			ft_comp(id, "F", 1) == TRUE || ft_comp(id, "C", 1) == TRUE)
		return (TRUE);
	return (FALSE);
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

	i = 0;
	id_counter = 0;
	while (game->file[i])
	{
		if (ft_is_identifier(game->file[i]) == TRUE)
		{
			printf("%d : %s\n", i, game->file[i]);
			id_counter++;
		}
		i++;
	}
	if (id_counter != 6)
		return (printf("numbers of id : %d\n", id_counter), exit_game(game, "Error: all identifers not found at the beginning of the file\n\n\n"), FALSE);
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
		return (FALSE);
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (TRUE);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_extension_checker.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:47:30 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/15 13:02:57 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	ft_find_path_to_textures(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	while (line[i] && ft_is_identifier(&line[i]) > 0)
		i += 2;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	ft_is_valid_path(char *path)
{
	// int	fd;
	// fd = open(path, O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("Error: textures path doesnt exist or cant be read\n");
	// 	return (FALSE);
	// }
	// close(fd);
	if (ft_check_extension(path, ".xpm", 4) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	ft_init_textures_extension_checker(t_game *game)
{
	int	i;
	int	path_index;
	int	invalid_path_counter;
	int	valid_path_counter;

	invalid_path_counter = 0;
	valid_path_counter = 0;
	i = 0;
	while (1)
	{
		while (game->file[i] && ft_is_line_empty(game->file[i]) == TRUE)
			i++;
		while (game->file[i])
		{
			path_index = ft_find_path_to_textures(game->file[i]);
			if (path_index == -1)
				i++;
			else if (ft_is_valid_path(&game->file[i][path_index]) == FALSE)
				invalid_path_counter++;
			else
				valid_path_counter++;
			i++;
		}
		if (invalid_path_counter > 0)
			return (FALSE);
		else if (valid_path_counter == 4)
			break ;
	}
	return (TRUE);
}

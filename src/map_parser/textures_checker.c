/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:47:30 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/01 14:20:14 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int ft_find_path_to_textures(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] && ft_is_identifier(&line[i]) > 0)
		i += 2;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int ft_is_valid_extension(char *path)
{
	if (ft_check_extension(path, ".xpm", 4) == FALSE)
		return (FALSE);
	return (TRUE);
}

int ft_is_valid_path(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	// if (fd < 0)
	// {
	// 	printf("Error: textures path doesnt exist or cant be read\n");
	// 	return (FALSE);
	// }
	close(fd);
	return (TRUE);
}

int ft_textures_checker(char *line, int *valid_path_counter)
{
	int path_index;

	path_index = ft_find_path_to_textures(line);
	if (ft_is_valid_path(&line[path_index]) == FALSE || ft_is_valid_extension(&line[path_index]) == FALSE)
		return (FALSE);
	(*valid_path_counter)++;
	return (TRUE);
}

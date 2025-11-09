/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_map_at_the_end.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:57:23 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:52:50 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	ft_is_char_accepted_in_map(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (TRUE);
	return (FALSE);
}

int	ft_start_index_of_the_map(char **file)
{
	int	i;

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

int	ft_end_index_of_the_map(char **file, int first_line)
{
	int	i;

	i = first_line;
	while (file[i + 1] && ft_is_identifier(file[i + 1]) == 0
		&& ft_is_line_empty(file[i + 1]) == FALSE)
		i++;
	return (i);
}

int	ft_find_last_index(int index, char **file)
{
	int	i;

	i = index;
	while (file[i])
		i++;
	return (i);
}

int	ft_map_is_at_the_end(char **file)
{
	int	start_of_the_map;
	int	end_of_the_map;
	int	end_of_file;
	int	i;

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

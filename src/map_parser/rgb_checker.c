/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:51:45 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/10 14:24:18 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	ft_is_valid_rgb(char *rgb)
{
	char	**rgb_values;
	int		i;
	int		k;

	rgb_values = ft_split(rgb, ',');
	if (!rgb_values)
		return (FALSE);
	if (ft_array_size(rgb_values) != 3)
		return (free_all(rgb_values), FALSE);
	i = 0;
	while (rgb_values[i])
	{
		k = 0;
		while (rgb_values[i][k] && ft_isspace(rgb_values[i][k]) == TRUE)
			k++;
		if (rgb_values[i][k] == '\0' || !ft_isdigit(rgb_values[i][k]))
			return (free_all(rgb_values), FALSE);
		if (ft_atoi(&rgb_values[i][k]) < 0 || ft_atoi(&rgb_values[i][k]) > 255)
			return (free_all(rgb_values), FALSE);
		i++;
	}
	return (free_all(rgb_values), TRUE);
}

int	ft_index_of_first_rgb(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (ft_is_identifier(&line[i]) == 2)
		i++;
	while (line[i] && ft_isspace(line[i]) == TRUE)
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	ft_rgb_checker(char *line, int *valid_rgb_counter)
{
	int	j;

	j = ft_index_of_first_rgb(line);
	if (ft_is_valid_rgb(&line[j]) == FALSE)
		return (printf("Error: invalid rgb: %s\n", &line[j]), FALSE);
	printf("Valid rgb: %s\n", &line[j]);
	(*valid_rgb_counter)++;
	return (TRUE);
}

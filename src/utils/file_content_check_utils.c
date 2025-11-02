/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:05:21 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/02 18:34:24 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	collect_identifiers(char **file, char id[7], int *id_counter)
{
	int	i;
	int	id_index;
	int	j;

	i = 0;
	id_index = 0;
	while (file[i])
	{
		j = 0;
		if (ft_is_identifier(file[i]) > 0)
		{
			while (file[i][j] && ft_isspace(file[i][j]) == TRUE)
				j++;
			id[id_index++] = file[i][j];
			(*id_counter)++;
		}
		else if (*id_counter != 6 && ft_is_identifier(file[i]) == 0
			&& ft_is_line_empty(file[i]) == FALSE)
			return (ft_putstr_fd("Error: invalid line before identifiers\n", 2),
				FALSE);
		i++;
	}
	return (TRUE);
}

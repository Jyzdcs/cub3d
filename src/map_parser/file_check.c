/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:55:04 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/02 18:21:03 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	check_extension(char *file_path)
{
	size_t	len;
	char	*dot;

	if (!file_path)
		return (FALSE);
	len = ft_strlen(file_path);
	if (len < 5)
		return (1);
	dot = ft_strrchr(file_path, '.');
	if (!dot || dot == file_path)
		return (1);
	if (ft_strncmp(dot, ".cub", 5) == 0)
		return (TRUE);
	return (FALSE);
}

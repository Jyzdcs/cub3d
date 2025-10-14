/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:55:04 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/14 12:34:05 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	check_extension(char *file_path, char *extension, int extension_len)
{
	int		len;
	char	*dot;

	if (!file_path)
		return (FALSE);
	len = ft_strlen(file_path);
	if (len < extension_len)
		return (FALSE);
	dot = ft_strrchr(file_path, '.');
	if (!dot || dot == file_path)
		return (FALSE);
	if (ft_strncmp(dot, extension, extension_len) == 0)
		return (TRUE);
	return (FALSE);
}

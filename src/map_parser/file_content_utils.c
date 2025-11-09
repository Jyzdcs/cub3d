/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:55:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:54:10 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int	ft_comp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	while (s1[i] == s2[i] && (s1[i] && s2[i]))
		i++;
	if (!s2[i] && (s1[i] == ' ' || s1[i] == '\t'))
		return (TRUE);
	return (FALSE);
}

int	ft_is_identifier(char *id)
{
	int	i;

	i = 0;
	while (id[i] != '\0' && (id[i] == ' ' || id[i] == '\t'))
		i++;
	if (id[i] == '\0')
		return (0);
	if (ft_comp(&id[i], "NO") == TRUE || ft_comp(&id[i], "SO") == TRUE
		|| ft_comp(&id[i], "WE") == TRUE || ft_comp(&id[i], "EA") == TRUE)
		return (1);
	else if (ft_comp(&id[i], "F") == TRUE || ft_comp(&id[i], "C") == TRUE)
		return (2);
	return (0);
}

int	ft_is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) != TRUE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

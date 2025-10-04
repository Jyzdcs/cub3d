/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:51:20 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/04 18:12:54 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	**export_file_content(char *path)
{
	int		fd;
	int		i;
	char	**line;
	char	*buff;

	fd = open(path, O_RDONLY);
	i = 0;
	while (1)
	{
		buff = get_next_line(fd);
		i++;
		if (!buff)
			break ;
		free(buff);
	}
	close(fd);
	line = malloc(sizeof(char *) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	fd = open(path, O_RDONLY);
	while (1)
	{
		line[i++] = get_next_line(fd);
		if (!line[i])
			break ;
	}
	close(fd);
	return (line);
}

int	file_is_empty(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
		{
			if (ft_isspace(file[i][j]) == FALSE)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	parse_content(int fd, char *path)
{
	char	**file;

	file = NULL;
	(void)fd;
	file = export_file_content(path);
	if (!file)
		return (FALSE);
	if (file_is_empty(file) == TRUE)
		return (FALSE);
	// printf("%s\n", file[0]);
	// if (ft_strlen(file[0]) == 0)
	// {
	// 	free_all(file);
	// 	return (FALSE);
	// }
	return (TRUE);
}

// Return true si le content est bon
int	check_file_content(char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: file doesnt exist\n", 2);
		return (FALSE);
	}
	if (parse_content(fd, path) == FALSE)
		return (FALSE);
	close(fd);
	return (TRUE);
}
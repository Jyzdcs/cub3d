#include "../include/map_parser.h"

// Fonction utilitaire:
char	**create_map_copy(t_map *map)
{
	int		i;
	int		j;
	char	**map_copy;

	i = 0;
	j = 0;
	map_copy = malloc(sizeof(char *) * map->height);
	if (!map_copy)
		return (NULL);
	while (i < map->height)
	{
		map_copy[i] = ft_strdup(map->map[i]);
		if (!map_copy[i])
		{
			while (j < i)
				free(map_copy[j]);
			free(map_copy);
			return (NULL);
			j++;
		}
		i++;
	}
	return (map_copy);
}

void	free_map_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

#include "../../include/map_parser.h"

int	map_have_one_player(char **map)
{
	int	player_count;
	int	i;
	int	j;

	player_count= 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] == '0' || map[i][j] == ' ' || map[i][j] == '1')
			j++;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (FALSE);
	return (TRUE);
}

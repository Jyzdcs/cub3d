#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

// Transmettre les x et y du player pour que le flood fill commence de là
// Part de la position du player et verifie si toute la map est accessible sans sortir des
// bounds de la map, si il y a une sortie de la map car ouverte,
// on set la data a 1
// pour que map_is_closed puisse la process et agir en fonction.
void	flood_fill(t_map *map, char **map_copy, int x, int y)
{
	if (map->is_closed)
		return ;
	if (x < 0 || y < 0 || y >= map->height)
	{
		map->is_closed = FALSE;
		return ;
	}
	if (x >= ft_strlen(map_copy[y]))
	{
		map->is_closed = FALSE;
		return ;
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map, map_copy, x + 1, y);
	flood_fill(map, map_copy, x - 1, y);
	flood_fill(map, map_copy, x, y + 1);
	flood_fill(map, map_copy, x, y - 1);
}

// On va d'abord check que le personnage est dans la map,
// dans le cas particulier
// ou on mettrait un N/S/E/W en dehors de la map et que la position du player soit donc
// en dehors.
// Ensuite on va faire un flood fill pour verifier si la map est fermee.
int	map_is_closed(char **map_copy, t_map *map, t_player *player)
{
	if (player->x < 0 || player->y < 0 || player->y >= map->height
		|| player->x >= ft_strlen(map_copy[player->y]))
	{
		map->is_closed = FALSE;
		return (FALSE);
	}
	flood_fill(map, map_copy, player->x, player->y);
	if (map->is_closed)
		return (FALSE);
	return (TRUE);
}

#include "../../include/raycasting.h"

// Traverse la grille case par case jusqu'à toucher un mur (algo DDA)
// Compare side_dist_x et side_dist_y à chaque étape pour avancer
// vers la ligne de grille la plus proche (verticale ou horizontale)
// void	dda_loop(t_ray *ray, t_game *game)
// {
// 	int hit;

// 	hit = 0;

// 	while (hit == 0)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->delta_dist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->delta_dist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}

// 		if (game->map.map[ray->map_y][ray->map_x] == '1')
// 		hit = 1;
// 	}
// }

// Dans ray_casting.c, ajoutez les vérifications:
void	dda_loop(t_ray *ray, t_game *game)
{
    int hit;
    int max_steps = 1000;
    int step_count = 0;

    hit = 0;

    while (hit == 0 && step_count < max_steps)
    {
        step_count++;

        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        // Vérifications de sécurité
        if (!game->map.map || ray->map_y < 0 || ray->map_y >= game->map.height ||
            !game->map.map[ray->map_y])
        {
            printf("ERROR: Invalid map access at ray->map_y=%d\n", ray->map_y);
            return;
        }
        if (ray->map_x < 0 || ray->map_x >= ft_strlen(game->map.map[ray->map_y]))
        {
            printf("ERROR: Invalid map access at ray->map_x=%d\n", ray->map_x);
            return;
        }

        char current_char = game->map.map[ray->map_y][ray->map_x];
        if (current_char == '1')
        {
            hit = 1;
        }
    }

    if (step_count >= max_steps)
    {
        printf("ERROR: DDA loop exceeded max steps (%d)\n", max_steps);
    }
}

// Détermine quelle texture utiliser (NO/SO/WE/EA) selon le côté
// du mur touché et la direction d'approche du rayon
// Side 0 == vertical, Side 1 == horizontal
void	determine_texture_id(t_ray *ray)
{

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->texture_id = 3;
		else
			ray->texture_id = 2;
	}
	else
	{
		if (ray->step_y > 0)
			ray->texture_id = 1;
		else
			ray->texture_id = 0;
	}
}

// Lance le rayon et trouve le premier mur touché
// Calcule la distance perpendiculaire, la texture à utiliser,
// et la position exacte sur le mur pour le texturing
void	cast_ray(t_ray *ray, t_game *game)
{
	dda_loop(ray, game);
	determine_texture_id(ray);

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;

	ray->wall_x -= floor(ray->wall_x);
}

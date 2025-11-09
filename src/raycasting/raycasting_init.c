/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:16:24 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:16:24 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"

// init_ray - Configure un rayon pour la colonne x de l'écran
//
// Chaque colonne voit une direction différente pour créer un FOV en éventail.
//
// 1. camera_x: normalise x de 0-WIDTH en -1 à +1 (gauche-centre-droite)
// 2. ray.dir: interpole entre (dir - plane) et (dir + plane) selon camera_x
//    → Balayage de la scène de gauche à droite
// 3. delta_dist: distance pour traverser 1 case (protégé contre division par 0)
// 4. init_dda_params: prépare l'algo de traversée de grille
//
// Le plane (perpendiculaire à dir) représente l'écran virtuel devant le joueur.
// Sa longueur (ex: 0.66) définit le FOV (~60° pour 0.66).
void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->camera.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->camera.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	init_dda_params(ray, game);
	ray->perp_wall_dist = 0;
	ray->side = 0;
	ray->texture_id = 0;
	ray->wall_x = 0;
}

// init_dda_params - Prépare les paramètres pour la traversée DDA
//
// Configure step et side_dist pour l'algo de traversée de grille:
//
// step_x/y: direction d'avancement dans la grille (+1 ou -1)
//	- Dépend du signe de ray.dir (positif = droite/bas, négatif = gauche/haut)
//
// side_dist_x/y: distance jusqu'à la prochaine ligne de grille
//	- Calcul: (distance en cases) * delta_dist
//	- Si dir_x > 0: distance = (map_x + 1) - player.x (ligne à droite)
//	- Si dir_x < 0: distance = player.x - map_x (ligne à gauche)
//	- Pareil pour Y
//
// Ces valeurs seront comparées dans la boucle DDA pour déterminer quelle
// ligne de grille croiser à chaque étape (verticale ou horizontale).
//
// EXEMPLE:
// player.x = 2.3, map_x = 2, dir_x = 0.7, delta_dist_x = 1.414
// → step_x = +1, side_dist_x = (3.0 - 2.3) * 1.414 = 0.99
void	init_dda_params(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

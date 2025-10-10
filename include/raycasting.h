/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:44 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/02 17:42:27 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include "cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x);
void	init_dda_params(t_ray *ray, t_game *game);
void	dda_loop(t_ray *ray, t_game *game);
void	determine_texture_id(t_ray *ray);
void	cast_ray(t_ray *ray, t_game *game);

#endif


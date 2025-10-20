/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/18 19:05:24 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parsing(t_game *game, int argc, char **argv)
{
	(void)game;
	if (argc != 2)
	{
		free(game);
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), FALSE);
	}
	if (ft_check_extension(argv[1], ".cub", 4) == FALSE || file_handler(argv[1],
			game) == FALSE)
	{
		free(game);
		return (ft_putstr_fd("Error: extension or file handler failed\n", 2),
			FALSE);
	}
	if (ft_textures_checker(game) == FALSE || ft_rgb_checker(game) == FALSE)
	{
		free_all(game->file);
		free(game);
		return (ft_putstr_fd("Error: textures checker failed\n", 2), FALSE);
	}
	free_all(game->file);
	free(game);
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (TRUE);
}

// int	main(int argc, char **argv)
// {
// 	t_game	*game;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
// 	if (parsing(game, argc, argv) == FALSE)
// 		return (1);
// 	return (0);
// }

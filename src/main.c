/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/15 13:03:53 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
	if (argc != 2)
	{
		free(game);
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	}
	if (ft_check_extension(argv[1], ".cub", 4) == FALSE || file_handler(argv[1],
			game) == FALSE)
	{
		free(game);
		return (1);
	}
	if (ft_init_textures_extension_checker(game) == FALSE)
	{
		free_all(game->file);
		free(game);
		return (1);
	}
	free_all(game->file);
	free(game);
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (0);
}

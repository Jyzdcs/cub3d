/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-02                              #+#    #+#             */
/*   Updated: 2025-10-02                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** This is run before EACH test, not just once for the whole test suite
*/
void	setUp(void)
{
	/* Initialize things needed by all tests here */
}

/*
** This is run after EACH test, not just once for the whole test suite
*/
void	tearDown(void)
{
	/* Clean up after each test */
}

/*
** Test function naming convention: test_ModuleName_FunctionName_Scenario
*/
void	test_init_player_data_find_north_player(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000N01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_EQUAL_CHAR('N', game->player.id);
	free(game);
}

void	test_init_player_data_find_south_player(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000S01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_EQUAL_CHAR('S', game->player.id);
	free(game);
}

void	test_init_player_data_find_east_player(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000E01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_EQUAL_CHAR('E', game->player.id);
	free(game);
}

void	test_init_player_data_find_west_player(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000W01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_EQUAL_CHAR('W', game->player.id);
	free(game);
}

void	test_init_player_data_north_direction(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000N01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.5, game->player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, game->player.y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.5, game->player.old_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, game->player.old_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -1.0, game->player.dir_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.66, game->camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->camera.plane_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.07, game->player.speed);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.05, game->player.rotation_speed);
	TEST_ASSERT_EQUAL_CHAR('N', game->player.id);
	free(game);
}

void	test_init_player_data_south_direction(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000S01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.5, game->player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, game->player.y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.0, game->player.dir_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -0.66, game->camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->camera.plane_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.07, game->player.speed);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.05, game->player.rotation_speed);
	TEST_ASSERT_EQUAL_CHAR('S', game->player.id);
	free(game);
}

void	test_init_player_data_east_direction(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000E01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.5, game->player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, game->player.y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.0, game->player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->player.dir_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.66, game->camera.plane_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.07, game->player.speed);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.05, game->player.rotation_speed);
	TEST_ASSERT_EQUAL_CHAR('E', game->player.id);
	free(game);
}

void	test_init_player_data_west_direction(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000W01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 4.0;
	game->player.y = 2.0;
	init_player_data(game);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.5, game->player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.5, game->player.y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -1.0, game->player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->player.dir_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, game->camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -0.66, game->camera.plane_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.07, game->player.speed);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.05, game->player.rotation_speed);
	TEST_ASSERT_EQUAL_CHAR('W', game->player.id);
	free(game);
}

void	test_init_player_data_player_position_centered(void)
{
	t_game		*game;
	static char	line0[] = "1111111";
	static char	line1[] = "1000001";
	static char	line2[] = "1000N01";
	static char	line3[] = "1111111";
	static char	*map[] = {line0, line1, line2, line3, NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->map.map = map;
	game->player.x = 3.0;
	game->player.y = 1.0;
	init_player_data(game);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 3.5, game->player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.5, game->player.y);
	free(game);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_init_player_data_find_north_player);
	RUN_TEST(test_init_player_data_find_south_player);
	RUN_TEST(test_init_player_data_find_east_player);
	RUN_TEST(test_init_player_data_find_west_player);
	RUN_TEST(test_init_player_data_north_direction);
	RUN_TEST(test_init_player_data_south_direction);
	RUN_TEST(test_init_player_data_east_direction);
	RUN_TEST(test_init_player_data_west_direction);
	RUN_TEST(test_init_player_data_player_position_centered);
	/* Return failure count from Unity */
	return (UNITY_END());
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-02                              #+#    #+#             */
/*   Updated: 2025-10-02                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>

/*
** This is run before EACH test, not just once for the whole test suite
*/
void setUp(void)
{
	/* Initialize things needed by all tests here */
}

/*
** This is run after EACH test, not just once for the whole test suite
*/
void tearDown(void)
{
	/* Clean up after each test */
}

/*
** Test function naming convention: test_ModuleName_FunctionName_Scenario
*/
void test_init_game_rgb_positive_numbers(void)
{
	t_game *game;
	int floor_color = 220 << 16 | 100 << 8 | 0;
	int ceiling_color = 225 << 16 | 30 << 8 | 0;
	char *test_file[] = {
			"NO ./maps/xpm/north.xpm",
			"SO ./maps/xpm/south.xpm",
			"WE ./maps/xpm/west.xpm",
			"EA ./maps/xpm/east.xpm",
			"                     ",
			"F 220,100,0",
			"C 225,30,0",
			"                     ",
			"1111111",
			"1000001",
			"1000N01",
			"1111111",
			NULL};

	/* Setup */
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->file = test_file;

	/* Execute */
	init_game_rgb(game);

	/* Verify texture paths are set */
	TEST_ASSERT_EQUAL_INT(floor_color, game->map.floor_color);
	TEST_ASSERT_EQUAL_INT(ceiling_color, game->map.ceiling_color);

	/* Verify specific paths if needed */
}

void test_init_game_rgb_white_space(void)
{
	t_game *game;
	int floor_color = 220 << 16 | 100 << 8 | 0;
	int ceiling_color = 225 << 16 | 30 << 8 | 200;
	char *test_file[] = {
			"NO 				./maps/xpm/north.xpm",
			"                     ",
			"							SO     ./maps/xpm/south.xpm",
			"WE ./maps/xpm/west.xpm",
			"                     ",
			"               EA  	./maps/xpm/east.xpm",
			"                     ",
			"			F 			220,     100,0",
			"  C 225		,			30 ,		200",
			"                     ",
			"1111111",
			"1000001",
			"1000N01",
			"1111111",
			NULL};

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->file = test_file;

	/* Execute */
	init_game_rgb(game);

	/* Verify texture paths are set */
	TEST_ASSERT_EQUAL_INT(floor_color, game->map.floor_color);
	TEST_ASSERT_EQUAL_INT(ceiling_color, game->map.ceiling_color);

	/* Verify specific paths if needed */
}

/*
** Main function to run all tests
*/
int main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_init_game_rgb_positive_numbers);
	RUN_TEST(test_init_game_rgb_white_space);
	/* Return failure count from Unity */
	return (UNITY_END());
}

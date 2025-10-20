/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:45:00 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/20 15:46:42 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>

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

/* Edge case: Simple valid map with one player and closed walls */
void	test_map_is_valid_simple_closed_map(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/* Edge case: Map with spaces at the start of some lines */
void	test_map_is_valid_map_with_leading_spaces(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 8);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("    111111111");
	game->file[1] = ft_strdup("    100000001");
	game->file[2] = ft_strdup("    1000N0001");
	game->file[3] = ft_strdup("    100000001");
	game->file[4] = ft_strdup("1111100000001");
	game->file[5] = ft_strdup("1000000000001");
	game->file[6] = ft_strdup("1111111111111");
	game->file[7] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 8);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/* Edge case: Larger valid map with player in center */
void	test_map_is_valid_larger_map(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 11);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("111111111");
	game->file[1] = ft_strdup("100000001");
	game->file[2] = ft_strdup("100000001");
	game->file[3] = ft_strdup("100000001");
	game->file[4] = ft_strdup("1000S0001");
	game->file[5] = ft_strdup("100000001");
	game->file[6] = ft_strdup("100000001");
	game->file[7] = ft_strdup("100000001");
	game->file[8] = ft_strdup("100000001");
	game->file[9] = ft_strdup("111111111");
	game->file[10] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 11);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/* Error case: Map is not closed (hole in north wall) */
void	test_map_is_valid_map_not_closed_north(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11011");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Map is not closed (hole in south wall) */
void	test_map_is_valid_map_not_closed_south(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11011");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Map is not closed (hole in east wall) */
void	test_map_is_valid_map_not_closed_east(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("10000");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Map is not closed (hole in west wall) */
void	test_map_is_valid_map_not_closed_west(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("00001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Player out of map bounds */
void	test_map_is_valid_player_out_of_map(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("N0001");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Multiple players in map */
void	test_map_is_valid_multiple_players(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 7);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10N01");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10S01");
	game->file[4] = ft_strdup("10001");
	game->file[5] = ft_strdup("11111");
	game->file[6] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 7);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Multiple players with different directions */
void	test_map_is_valid_multiple_players_different_directions(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 7);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10E01");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10W01");
	game->file[4] = ft_strdup("10001");
	game->file[5] = ft_strdup("11111");
	game->file[6] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 7);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Error case: Zero players in map */
void	test_map_is_valid_zero_players(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10001");
	game->file[2] = ft_strdup("10001");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/* Edge case: Player at different valid positions (North) */
void	test_map_is_valid_player_direction_north(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10001");
	game->file[2] = ft_strdup("10N01");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/* Edge case: Player at different valid positions (East) */
void	test_map_is_valid_player_direction_east(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10001");
	game->file[2] = ft_strdup("10E01");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/* Edge case: Player at different valid positions (West) */
void	test_map_is_valid_player_direction_west(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("11111");
	game->file[1] = ft_strdup("10001");
	game->file[2] = ft_strdup("10W01");
	game->file[3] = ft_strdup("10001");
	game->file[4] = ft_strdup("11111");
	game->file[5] = NULL;
	/* Allocate space for map.map */
	game->map.map = malloc(sizeof(char *) * 6);
	/* Test the function */
	result = map_is_valid(game);
	/* Clean up */
	free_all(game->file);
	free_all(game->map.map);
	free(game);
	/* Assertion */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_map_is_valid_simple_closed_map);
	RUN_TEST(test_map_is_valid_map_with_leading_spaces);
	RUN_TEST(test_map_is_valid_larger_map);
	RUN_TEST(test_map_is_valid_map_not_closed_north);
	RUN_TEST(test_map_is_valid_map_not_closed_south);
	RUN_TEST(test_map_is_valid_map_not_closed_east);
	RUN_TEST(test_map_is_valid_map_not_closed_west);
	RUN_TEST(test_map_is_valid_player_out_of_map);
	RUN_TEST(test_map_is_valid_multiple_players);
	RUN_TEST(test_map_is_valid_multiple_players_different_directions);
	RUN_TEST(test_map_is_valid_zero_players);
	RUN_TEST(test_map_is_valid_player_direction_north);
	RUN_TEST(test_map_is_valid_player_direction_east);
	RUN_TEST(test_map_is_valid_player_direction_west);
	/* Return failure count from Unity */
	return (UNITY_END());
}

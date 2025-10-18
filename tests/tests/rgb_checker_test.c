
#include "../../include/cub3d.h"
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
void	test_rgb_edge_cases(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 10);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("F 255,255,255");
	game->file[1] = ft_strdup("C 255,255,255");
	game->file[2] = ft_strdup("											");
	game->file[3] = ft_strdup("NO ./texture.xpm");
	game->file[4] = ft_strdup("SO ./texture.xpm");
	game->file[5] = ft_strdup("WE ./texture.xpm");
	game->file[6] = ft_strdup("EA ./texture.xpm");
	game->file[7] = ft_strdup("											");
	game->file[8] = ft_strdup("11111");
	game->file[9] = NULL;
	result = ft_rgb_checker(game);
	free_all(game->file);
	free(game);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_rgb_invalid_rgb_value(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 5);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("F 255,255,256");
	game->file[1] = ft_strdup("C 255,255,255");
	game->file[2] = NULL;
	result = ft_rgb_checker(game);
	free_all(game->file);
	free(game);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_rgb_2_values_only_with_comma(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 5);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("F 255,255, ");
	game->file[1] = ft_strdup("C 255,255,255");
	game->file[2] = NULL;
	result = ft_rgb_checker(game);
	free_all(game->file);
	free(game);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_rgb_good_values_with_space(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 5);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("     F 		0,     34,           255");
	game->file[1] = ft_strdup("C 155,					255, 54");
	game->file[2] = NULL;
	result = ft_rgb_checker(game);
	free_all(game->file);
	free(game);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_rgb_good_values_with_empty_lines_and_whitespace(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 6);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("											");
	game->file[1] = ft_strdup("     F 		255,     255,           255");
	game->file[2] = ft_strdup("											");
	game->file[3] = ft_strdup("											");
	game->file[4] = ft_strdup("C 255,					255, 255");
	game->file[5] = NULL;
	result = ft_rgb_checker(game);
	free_all(game->file);
	free(game);
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
	RUN_TEST(test_rgb_edge_cases);
	RUN_TEST(test_rgb_invalid_rgb_value);
	RUN_TEST(test_rgb_2_values_only_with_comma);
	RUN_TEST(test_rgb_good_values_with_space);
	RUN_TEST(test_rgb_good_values_with_empty_lines_and_whitespace);
	/* Return failure count from Unity */
	return (UNITY_END());
}


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
void	test_line_with_only_whitespace(void)
{
	int	result;

	/* Example function we might be testing */
	result = ft_find_path_to_textures("          ");
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(-1, result);
}

void	test_find_path_to_textures_with_whitespace_and_no_identifier(void)
{
	int	result;

	/* Example function we might be testing */
	result = ft_find_path_to_textures("                  /texture.xpm");
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(18, result);
}

void	test_find_path_to_textures_with_whitespace_and_identifier(void)
{
	int	result;

	/* Example function we might be testing */
	result = ft_find_path_to_textures("                  NO /texture.xpm");
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(21, result);
}

void	test_find_path_to_textures_with_whitespace_and_identifier_and_no_path(void)
{
	int	result;

	/* Example function we might be testing */
	result = ft_find_path_to_textures("                  NO ");
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(-1, result);
}

void	test_find_path_to_textures_edge_case(void)
{
	int	result;

	/* Example function we might be testing */
	result = ft_find_path_to_textures("NO /texture.xpm");
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(3, result);
}

void	test_init_textures_extension_checker_edge_case(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 5);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("NO /texture.xpm");
	game->file[1] = ft_strdup("SO /texture.xpm");
	game->file[2] = ft_strdup("WE /texture.xpm");
	game->file[3] = ft_strdup("EA /texture.xpm");
	game->file[4] = NULL;
	/* Example function we might be testing */
	result = ft_init_textures_extension_checker(game);
	free_all(game->file);
	free(game);
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_init_textures_extension_bad_extension(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 2);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("NO /texture.jpg");
	game->file[1] = NULL;
	/* Example function we might be testing */
	result = ft_init_textures_extension_checker(game);
	free_all(game->file);
	free(game);
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_init_textures_extension_multiple_bad_extension(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 2);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("NO /texture.xpm");
	game->file[1] = ft_strdup("SO /texture.jpg");
	game->file[2] = ft_strdup("WE /texture.xpm");
	game->file[3] = ft_strdup("EA /texture.jpg");
	game->file[4] = NULL;
	/* Example function we might be testing */
	result = ft_init_textures_extension_checker(game);
	free_all(game->file);
	free(game);
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_init_textures_extension_checker_whitespace(void)
{
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	game->file = malloc(sizeof(char *) * 8);
	if (!game->file)
		return ;
	game->file[0] = ft_strdup("											");
	game->file[1] = ft_strdup("NO           /texture.xpm");
	game->file[2] = ft_strdup("         SO /texture.xpm");
	game->file[3] = ft_strdup("  WE     /texture.xpm");
	game->file[4] = ft_strdup("								");
	game->file[5] = ft_strdup("");
	game->file[6] = ft_strdup("EA /texture.xpm");
	game->file[7] = NULL;
	/* Example function we might be testing */
	result = ft_init_textures_extension_checker(game);
	free_all(game->file);
	free(game);
	/* Assertions - different types you might use */
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
	RUN_TEST(test_find_path_to_textures_with_whitespace_and_no_identifier);
	RUN_TEST(test_line_with_only_whitespace);
	RUN_TEST(test_find_path_to_textures_with_whitespace_and_identifier);
	RUN_TEST(test_find_path_to_textures_with_whitespace_and_identifier_and_no_path);
	RUN_TEST(test_find_path_to_textures_edge_case);
	RUN_TEST(test_init_textures_extension_checker_edge_case);
	RUN_TEST(test_init_textures_extension_checker_whitespace);
	RUN_TEST(test_init_textures_extension_bad_extension);
	RUN_TEST(test_init_textures_extension_multiple_bad_extension);
	/* Return failure count from Unity */
	return (UNITY_END());
}

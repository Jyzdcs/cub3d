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
void	test_parsing_edge_case(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/subject_map.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_bad_number_of_arguments(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 3;
	argv = malloc(sizeof(char *) * 4);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/subject_map.cub";
	argv[2] = "../maps/good/subject_map.cub";
	argv[3] = NULL;
	result = parsing(game, argc, argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_bad_extension(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/bad_extension.txt";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_color_invalid_rgb(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/color_invalid_rgb.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_color_missing_ceiling_rgb(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/color_missing_ceiling_rgb.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_color_missing_floor_rgb(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/color_missing_floor_rgb.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_color_missing(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/color_missing.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_color_none(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/color_none.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_custom_map(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/custom_map.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

void	test_parsing_empty_map(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/empty_map.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_file_letter_end(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/file_letter_end.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_filtetype_missing(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/filtetype_missing.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_filetype_wrong(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/filetype_wrong.buc";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

// void	test_parsing_forbidden(void)
// {
// 	int		argc;
// 	char	**argv;
// 	int		result;
// 	t_game	*game;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		return ;
// 	argc = 2;
// 	argv = malloc(sizeof(char *) * 3);
// 	if (!argv)
// 		return ;
// 	argv[0] = "./cub3d";
// 	argv[1] = "../maps/bad/forbidden.cub";
// 	argv[2] = NULL;
// 	result = parsing(game, argc, argv);
// 	free(argv);
// 	TEST_ASSERT_EQUAL_INT(FALSE, result);
// }

void	test_parsing_map_first(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/map_first.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_map_middle(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/map_middle.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_map_missing(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/map_missing.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_map_only(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/map_only.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_too_small(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/map_too_small.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_player_multiple(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/player_multiple.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_player_none(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/player_none.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_player_on_edge(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/player_on_edge.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_dir(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_dir.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_duplicates(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_duplicates.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_duplicates_2(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_duplicates_2.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_forbidden(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_forbidden.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_invalid(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_invalid.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_missing(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_missing.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_name_modified(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_name_modified.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_none(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_none.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_textures_not_xpm(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/textures_not_xpm.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_wall_hole_east(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/wall_hole_east.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_wall_hole_north(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/wall_hole_north.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_wall_hole_south(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/wall_hole_south.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_wall_hole_west(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/wall_hole_west.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_wall_none(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/bad/wall_none.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_parsing_good_cheese_maze(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/cheese_maze.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_creepy(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/creepy.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_dungeon(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/dungeon.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_library(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/library.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_matrix(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/matrix.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_sad_face(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/sad_face.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_square_map(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/square_map.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_map(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_map.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_map_hole(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_map_hole.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_pos_bottom(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_pos_bottom.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_pos_left(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_pos_left.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_pos_right(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_pos_right.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_pos_top(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_pos_top.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_textures(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_textures.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_test_whitespace(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/test_whitespace.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_parsing_good_works(void)
{
	int		argc;
	char	**argv;
	int		result;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return ;
	argc = 2;
	argv = malloc(sizeof(char *) * 3);
	if (!argv)
		return ;
	argv[0] = "./cub3d";
	argv[1] = "../maps/good/works.cub";
	argv[2] = NULL;
	result = parsing(game, argc, argv);
	free(argv);
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
	RUN_TEST(test_parsing_edge_case);
	RUN_TEST(test_parsing_bad_number_of_arguments);
	RUN_TEST(test_parsing_bad_extension);
	RUN_TEST(test_parsing_color_invalid_rgb);
	RUN_TEST(test_parsing_color_missing_ceiling_rgb);
	RUN_TEST(test_parsing_color_missing_floor_rgb);
	RUN_TEST(test_parsing_color_missing);
	RUN_TEST(test_parsing_color_none);
	RUN_TEST(test_parsing_custom_map);
	RUN_TEST(test_parsing_empty_map);
	RUN_TEST(test_parsing_file_letter_end);
	RUN_TEST(test_parsing_filtetype_missing);
	RUN_TEST(test_parsing_filetype_wrong);
	// RUN_TEST(test_parsing_forbidden);
	RUN_TEST(test_parsing_map_first);
	RUN_TEST(test_parsing_map_middle);
	RUN_TEST(test_parsing_map_missing);
	RUN_TEST(test_parsing_map_only);
	RUN_TEST(test_parsing_too_small);
	RUN_TEST(test_parsing_player_multiple);
	RUN_TEST(test_parsing_player_none);
	RUN_TEST(test_parsing_player_on_edge);
	RUN_TEST(test_parsing_textures_dir);
	RUN_TEST(test_parsing_textures_duplicates);
	RUN_TEST(test_parsing_textures_duplicates_2);
	// RUN_TEST(test_parsing_textures_forbidden);
	RUN_TEST(test_parsing_textures_invalid);
	RUN_TEST(test_parsing_textures_missing);
	RUN_TEST(test_parsing_textures_name_modified);
	RUN_TEST(test_parsing_textures_none);
	RUN_TEST(test_parsing_textures_not_xpm);
	RUN_TEST(test_parsing_wall_hole_east);
	RUN_TEST(test_parsing_wall_hole_north);
	RUN_TEST(test_parsing_wall_hole_south);
	RUN_TEST(test_parsing_wall_hole_west);
	RUN_TEST(test_parsing_wall_none);
	RUN_TEST(test_parsing_good_cheese_maze);
	RUN_TEST(test_parsing_good_creepy);
	RUN_TEST(test_parsing_good_dungeon);
	RUN_TEST(test_parsing_good_library);
	RUN_TEST(test_parsing_good_matrix);
	RUN_TEST(test_parsing_good_sad_face);
	RUN_TEST(test_parsing_good_square_map);
	RUN_TEST(test_parsing_good_test_map);
	RUN_TEST(test_parsing_good_test_map_hole);
	RUN_TEST(test_parsing_good_test_pos_bottom);
	RUN_TEST(test_parsing_good_test_pos_left);
	RUN_TEST(test_parsing_good_test_pos_right);
	RUN_TEST(test_parsing_good_test_pos_top);
	RUN_TEST(test_parsing_good_test_textures);
	RUN_TEST(test_parsing_good_test_whitespace);
	RUN_TEST(test_parsing_good_works);
	/* Return failure count from Unity */
	return (UNITY_END());
}

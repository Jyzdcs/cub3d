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
void test_init_game_walls_paths_edge_cases(void)
{
	t_game *game;
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
	init_game_walls_paths_and_colors(game);

	/* Verify texture paths are set */
	TEST_ASSERT_NOT_NULL(game->map.no_wall);
	TEST_ASSERT_NOT_NULL(game->map.so_wall);
	TEST_ASSERT_NOT_NULL(game->map.we_wall);
	TEST_ASSERT_NOT_NULL(game->map.ea_wall);

	/* Verify specific paths if needed */
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/north.xpm", game->map.no_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/south.xpm", game->map.so_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/west.xpm", game->map.we_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/east.xpm", game->map.ea_wall);
	TEST_ASSERT_EQUAL_INT(220 << 16 | 100 << 8 | 0, game->map.floor_color);
	TEST_ASSERT_EQUAL_INT(225 << 16 | 30 << 8 | 0, game->map.ceiling_color);
}

void test_init_game_walls_paths_white_space(void)
{
	t_game *game;
	char *test_file[] = {
			"NO 				./maps/xpm/north.xpm",
			"                     ",
			"							SO     ./maps/xpm/south.xpm",
			"WE ./maps/xpm/west.xpm",
			"                     ",
			"               EA  	./maps/xpm/east.xpm",
			"                     ",
			"F 220,100,0",
			"C 225,30,0",
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
	init_game_walls_paths_and_colors(game);

	/* Verify texture paths are set */
	TEST_ASSERT_NOT_NULL(game->map.no_wall);
	TEST_ASSERT_NOT_NULL(game->map.so_wall);
	TEST_ASSERT_NOT_NULL(game->map.we_wall);
	TEST_ASSERT_NOT_NULL(game->map.ea_wall);

	/* Verify specific paths if needed */
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/north.xpm", game->map.no_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/south.xpm", game->map.so_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/west.xpm", game->map.we_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/east.xpm", game->map.ea_wall);
	TEST_ASSERT_EQUAL_INT(220 << 16 | 100 << 8 | 0, game->map.floor_color);
	TEST_ASSERT_EQUAL_INT(225 << 16 | 30 << 8 | 0, game->map.ceiling_color);
}

void test_init_game_walls_paths_floor_and_ceiling_color(void)
{
	t_game *game;
	char *test_file[] = {
			"			  NO 		./maps/xpm/north.xpm",
			"			F    220,100,0",
			"						",
			"SO ./maps/xpm/south.xpm",
			"						",
			"WE ./maps/xpm/west.xpm",
			"						",
			"EA ./maps/xpm/east.xpm",
			"						",
			"						",
			"C 225,30,0",
			"						",
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
	init_game_walls_paths_and_colors(game);

	/* Verify texture paths are set */
	TEST_ASSERT_NOT_NULL(game->map.no_wall);
	TEST_ASSERT_NOT_NULL(game->map.so_wall);
	TEST_ASSERT_NOT_NULL(game->map.we_wall);
	TEST_ASSERT_NOT_NULL(game->map.ea_wall);

	/* Verify specific paths if needed */
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/north.xpm", game->map.no_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/south.xpm", game->map.so_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/west.xpm", game->map.we_wall);
	TEST_ASSERT_EQUAL_STRING("./maps/xpm/east.xpm", game->map.ea_wall);
	TEST_ASSERT_EQUAL_INT(220 << 16 | 100 << 8 | 0, game->map.floor_color);
	TEST_ASSERT_EQUAL_INT(225 << 16 | 30 << 8 | 0, game->map.ceiling_color);
}

void test_load_all_textures_edge_cases(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: mlx_init\n", 2));
	game->map.no_wall = "../maps/xpm/north.xpm";
	game->map.so_wall = "../maps/xpm/south.xpm";
	game->map.we_wall = "../maps/xpm/west.xpm";
	game->map.ea_wall = "../maps/xpm/east.xpm";

	/* Execute */
	load_all_textures(game);

	/* Verify texture addresses are not NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.img);
	TEST_ASSERT_NOT_NULL(game->so_texture.img);
	TEST_ASSERT_NOT_NULL(game->we_texture.img);
	TEST_ASSERT_NOT_NULL(game->ea_texture.img);
	/* Verify texture addresses are not NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.addr);
	TEST_ASSERT_NOT_NULL(game->so_texture.addr);
	TEST_ASSERT_NOT_NULL(game->we_texture.addr);
	TEST_ASSERT_NOT_NULL(game->ea_texture.addr);
	/* Verify texture paths are set */
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->no_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->so_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->we_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->ea_texture.addr);
}

void test_load_all_textures_invalid_path(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: mlx_init\n", 2));
	game->map.no_wall = "../maps/bad/textures_invalid.xpm";
	game->map.so_wall = "../maps/bad/textures_invalid.xpm";
	game->map.we_wall = "../maps/bad/textures_invalid.xpm";
	game->map.ea_wall = "../maps/bad/textures_invalid.xpm";

	/* Execute */
	load_all_textures(game);

	/* Verify texture addresses are NULL */
	TEST_ASSERT_NULL(game->no_texture.img);
	TEST_ASSERT_NULL(game->so_texture.img);
	TEST_ASSERT_NULL(game->we_texture.img);
	TEST_ASSERT_NULL(game->ea_texture.img);
	/* Verify texture addresses are NULL */
	TEST_ASSERT_NULL(game->no_texture.addr);
	TEST_ASSERT_NULL(game->so_texture.addr);
	TEST_ASSERT_NULL(game->we_texture.addr);
	TEST_ASSERT_NULL(game->ea_texture.addr);
}

void test_load_all_textures_with_one_texture_invalid(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: mlx_init\n", 2));
	game->map.no_wall = "../maps/xpm/north.xpm";
	game->map.so_wall = "../maps/bad/textures_invalid.xpm";
	game->map.we_wall = "../maps/xpm/west.xpm";
	game->map.ea_wall = "../maps/xpm/east.xpm";

	/* Execute */
	load_all_textures(game);
	/* Verify texture addresses are NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.img);
	TEST_ASSERT_NULL(game->so_texture.img);
	TEST_ASSERT_NULL(game->we_texture.img);
	TEST_ASSERT_NULL(game->ea_texture.img);
	/* Verify texture addresses are NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.addr);
	TEST_ASSERT_NULL(game->so_texture.addr);
	TEST_ASSERT_NULL(game->we_texture.addr);
	TEST_ASSERT_NULL(game->ea_texture.addr);
}

void test_init_game_textures_edge_cases(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2));
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putstr_fd("Error: mlx_init\n", 2));
	game->file = malloc(sizeof(char *) * 12);
	if (!game->file)
		return (ft_putstr_fd("Error: allocation memory on file\n", 2));
	game->file[0] = ft_strdup("NO ../maps/xpm/north.xpm");
	game->file[1] = ft_strdup("SO ../maps/xpm/south.xpm");
	game->file[2] = ft_strdup("WE ../maps/xpm/west.xpm");
	game->file[3] = ft_strdup("EA ../maps/xpm/east.xpm");
	game->file[4] = ft_strdup("F 220,100,0");
	game->file[5] = ft_strdup("C 225,30,0");
	game->file[6] = ft_strdup("                     ");
	game->file[7] = ft_strdup("1111111");
	game->file[8] = ft_strdup("1000001");
	game->file[9] = ft_strdup("1000N01");
	game->file[10] = ft_strdup("1111111");
	game->file[11] = NULL;

	/* Execute */
	init_game_textures(game);

	/* Verify texture paths are set */
	TEST_ASSERT_NOT_NULL(game->map.no_wall);
	TEST_ASSERT_NOT_NULL(game->map.so_wall);
	TEST_ASSERT_NOT_NULL(game->map.we_wall);
	TEST_ASSERT_NOT_NULL(game->map.ea_wall);

	/* Verify specific paths if needed */
	TEST_ASSERT_EQUAL_STRING("../maps/xpm/north.xpm", game->map.no_wall);
	TEST_ASSERT_EQUAL_STRING("../maps/xpm/south.xpm", game->map.so_wall);
	TEST_ASSERT_EQUAL_STRING("../maps/xpm/west.xpm", game->map.we_wall);
	TEST_ASSERT_EQUAL_STRING("../maps/xpm/east.xpm", game->map.ea_wall);

	/* Verify texture addresses are not NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.img);
	TEST_ASSERT_NOT_NULL(game->so_texture.img);
	TEST_ASSERT_NOT_NULL(game->we_texture.img);
	TEST_ASSERT_NOT_NULL(game->ea_texture.img);
	/* Verify texture addresses are not NULL */
	TEST_ASSERT_NOT_NULL(game->no_texture.addr);
	TEST_ASSERT_NOT_NULL(game->so_texture.addr);
	TEST_ASSERT_NOT_NULL(game->we_texture.addr);
	TEST_ASSERT_NOT_NULL(game->ea_texture.addr);
	/* Verify texture paths are set */
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->no_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->so_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->we_texture.addr);
	TEST_ASSERT_NOT_EQUAL_INT(FALSE, game->ea_texture.addr);
}

/*
** Main function to run all tests
*/
int main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_init_game_walls_paths_edge_cases);
	RUN_TEST(test_init_game_walls_paths_white_space);
	RUN_TEST(test_init_game_walls_paths_floor_and_ceiling_color);
	RUN_TEST(test_load_all_textures_edge_cases);
	RUN_TEST(test_load_all_textures_invalid_path);
	RUN_TEST(test_load_all_textures_with_one_texture_invalid);
	RUN_TEST(test_init_game_textures_edge_cases);
	/* Return failure count from Unity */
	return (UNITY_END());
}

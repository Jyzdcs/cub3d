/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-10                              #+#    #+#             */
/*   Updated: 2025-10-10                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"
#include "../Unity/src/unity.h"
#include <math.h>

/*
** This is run before EACH test
*/
void	setUp(void)
{
}

/*
** This is run after EACH test
*/
void	tearDown(void)
{
}

/*
** Test 1: Vérifie determine_texture_id pour mur Nord
*/
void	test_determine_texture_north_wall(void)
{
	t_ray	ray;

	ray.side = 1;
	ray.step_y = -1;
	determine_texture_id(&ray);
	TEST_ASSERT_EQUAL_INT(0, ray.texture_id);
}

/*
** Test 2: Vérifie determine_texture_id pour mur Sud
*/
void	test_determine_texture_south_wall(void)
{
	t_ray	ray;

	ray.side = 1;
	ray.step_y = 1;
	determine_texture_id(&ray);
	TEST_ASSERT_EQUAL_INT(1, ray.texture_id);
}

/*
** Test 3: Vérifie determine_texture_id pour mur Ouest
*/
void	test_determine_texture_west_wall(void)
{
	t_ray	ray;

	ray.side = 0;
	ray.step_x = -1;
	determine_texture_id(&ray);
	TEST_ASSERT_EQUAL_INT(2, ray.texture_id);
}

/*
** Test 4: Vérifie determine_texture_id pour mur Est
*/
void	test_determine_texture_east_wall(void)
{
	t_ray	ray;

	ray.side = 0;
	ray.step_x = 1;
	determine_texture_id(&ray);
	TEST_ASSERT_EQUAL_INT(3, ray.texture_id);
}

/*
** Test 5: DDA trouve un mur directement devant (Est)
*/
void	test_dda_wall_east(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	dda_loop(&ray, &game);
	TEST_ASSERT_EQUAL_INT(2, ray.map_x);
	TEST_ASSERT_EQUAL_INT(1, ray.map_y);
	TEST_ASSERT_EQUAL_INT(0, ray.side);
}

/*
** Test 6: DDA trouve un mur au Nord
*/
void	test_dda_wall_north(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 0.0;
	game.player.dir_y = -1.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.66;
	game.camera.plane_y = 0.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	dda_loop(&ray, &game);
	TEST_ASSERT_EQUAL_INT(1, ray.map_x);
	TEST_ASSERT_EQUAL_INT(0, ray.map_y);
	TEST_ASSERT_EQUAL_INT(1, ray.side);
}

/*
** Test 7: cast_ray calcule perp_wall_dist > 0
*/
void	test_cast_ray_perp_wall_dist_positive(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT(ray.perp_wall_dist > 0);
}

/*
** Test 8: cast_ray calcule wall_x dans [0, 1)
*/
void	test_cast_ray_wall_x_normalized(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT(ray.wall_x >= 0.0);
	TEST_ASSERT(ray.wall_x < 1.0);
}

/*
** Test 9: cast_ray définit texture_id correctement (mur Est)
*/
void	test_cast_ray_texture_east(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_EQUAL_INT(3, ray.texture_id);
}

/*
** Test 10: DDA dans couloir long (vérifier distance)
*/
void	test_dda_long_corridor(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {
		"1111111",
		"1000001",
		"1111111"
	};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 7;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT(ray.perp_wall_dist > 3.0);
	TEST_ASSERT(ray.perp_wall_dist < 6.0);
}

/*
** Test 11: Rayon diagonal (NE)
*/
void	test_dda_diagonal_northeast(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {
		"11111",
		"10001",
		"10001",
		"10001",
		"11111"
	};

	game.player.x = 2.5;
	game.player.y = 2.5;
	game.player.dir_x = 0.707;
	game.player.dir_y = -0.707;
	game.map.map = map_data;
	game.map.width = 5;
	game.map.height = 5;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	dda_loop(&ray, &game);
	TEST_ASSERT(ray.map_x == 4 || ray.map_y == 0);
}

/*
** Test 12: Vérifier side correct (vertical vs horizontal)
*/
void	test_dda_side_vertical(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	dda_loop(&ray, &game);
	TEST_ASSERT_EQUAL_INT(0, ray.side);
}

/*
** Test 13: Vérifier side correct (horizontal)
*/
void	test_dda_side_horizontal(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 0.0;
	game.player.dir_y = 1.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.66;
	game.camera.plane_y = 0.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	dda_loop(&ray, &game);
	TEST_ASSERT_EQUAL_INT(1, ray.side);
}

/*
** Test 14: Joueur exactement sur ligne de grille
** Edge case: position sans partie fractionnaire
*/
void	test_dda_player_on_grid_line(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 2.0;
	game.player.y = 1.0;
	game.player.dir_x = -1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT(ray.perp_wall_dist > 0);
	TEST_ASSERT(ray.wall_x >= 0.0 && ray.wall_x < 1.0);
}

/*
** Test 15: Vérifier distance exacte connue
** Joueur à 1.5, mur à 2.0 -> distance = 0.5
*/
void	test_cast_ray_exact_distance(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {"111", "101", "111"};

	game.player.x = 1.5;
	game.player.y = 1.5;
	game.player.dir_x = 1.0;
	game.player.dir_y = 0.0;
	game.map.map = map_data;
	game.map.width = 3;
	game.map.height = 3;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.5, ray.perp_wall_dist);
}

/*
** Test 16: Vérifier les 4 textures différentes
** NO=0, SO=1, WE=2, EA=3
*/
void	test_cast_ray_all_four_textures(void)
{
	t_game	game;
	t_ray	ray;
	char	*map_data[] = {
		"11111",
		"10001",
		"10001",
		"10001",
		"11111"
	};

	game.map.map = map_data;
	game.map.width = 5;
	game.map.height = 5;
	game.player.x = 2.5;
	game.player.y = 2.5;
	game.camera.plane_x = 0.0;
	game.camera.plane_y = 0.66;
	game.player.dir_x = 0.0;
	game.player.dir_y = -1.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_EQUAL_INT(0, ray.texture_id);
	game.player.dir_y = 1.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_EQUAL_INT(1, ray.texture_id);
	game.camera.plane_x = 0.66;
	game.camera.plane_y = 0.0;
	game.player.dir_x = -1.0;
	game.player.dir_y = 0.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_EQUAL_INT(2, ray.texture_id);
	game.player.dir_x = 1.0;
	init_ray(&ray, &game, SCREEN_WIDTH / 2);
	cast_ray(&ray, &game);
	TEST_ASSERT_EQUAL_INT(3, ray.texture_id);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_determine_texture_north_wall);
	RUN_TEST(test_determine_texture_south_wall);
	RUN_TEST(test_determine_texture_west_wall);
	RUN_TEST(test_determine_texture_east_wall);
	RUN_TEST(test_dda_wall_east);
	RUN_TEST(test_dda_wall_north);
	RUN_TEST(test_cast_ray_perp_wall_dist_positive);
	RUN_TEST(test_cast_ray_wall_x_normalized);
	RUN_TEST(test_cast_ray_texture_east);
	RUN_TEST(test_dda_long_corridor);
	RUN_TEST(test_dda_diagonal_northeast);
	RUN_TEST(test_dda_side_vertical);
	RUN_TEST(test_dda_side_horizontal);
	RUN_TEST(test_dda_player_on_grid_line);
	RUN_TEST(test_cast_ray_exact_distance);
	RUN_TEST(test_cast_ray_all_four_textures);
	return (UNITY_END());
}


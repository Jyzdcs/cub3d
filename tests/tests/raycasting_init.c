/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-02                              #+#    #+#             */
/*   Updated: 2025-10-02                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/raycasting.h"
#include "../Unity/src/unity.h"
#include <math.h>

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
** Test 1: Vérifie init_ray pour la colonne de gauche (x = 0)
** Le rayon doit pointer vers la gauche du FOV
*/
void	test_init_ray_left_column(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 0.0, .dir_y = -1.0},
		.camera = {.plane_x = 0.66, .plane_y = 0.0}
	};
	t_ray	ray;

	init_ray(&ray, &game, 0);

	/* Rayon doit pointer vers l'Ouest (x négatif car camera_x = -1) */
	TEST_ASSERT(ray.dir_x < 0);
	/* Position initiale doit correspondre à la position du joueur */
	TEST_ASSERT_EQUAL_INT(5, ray.map_x);
	TEST_ASSERT_EQUAL_INT(5, ray.map_y);
	/* Les résultats doivent être initialisés à 0 */
	TEST_ASSERT_EQUAL_DOUBLE(0.0, ray.perp_wall_dist);
	TEST_ASSERT_EQUAL_INT(0, ray.side);
	TEST_ASSERT_EQUAL_INT(0, ray.texture_id);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, ray.wall_x);
}

/*
** Test 2: Vérifie init_ray pour la colonne du centre
** Le rayon doit pointer dans la direction du joueur
*/
void	test_init_ray_center_column(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 1.0, .dir_y = 0.0},
		.camera = {.plane_x = 0.0, .plane_y = 0.66}
	};
	t_ray	ray;

	init_ray(&ray, &game, SCREEN_WIDTH / 2);

	/* Direction doit être approximativement égale à la direction du joueur */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 1.0, ray.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.0, ray.dir_y);
	TEST_ASSERT_EQUAL_INT(5, ray.map_x);
	TEST_ASSERT_EQUAL_INT(5, ray.map_y);
}

/*
** Test 3: Vérifie init_ray pour la colonne de droite (x = SCREEN_WIDTH - 1)
** Le rayon doit pointer vers la droite du FOV
*/
void	test_init_ray_right_column(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 0.0, .dir_y = -1.0},
		.camera = {.plane_x = 0.66, .plane_y = 0.0}
	};
	t_ray	ray;

	init_ray(&ray, &game, SCREEN_WIDTH - 1);

	/* Rayon doit pointer vers l'Est (x positif car camera_x ≈ 1) */
	TEST_ASSERT(ray.dir_x > 0);
	TEST_ASSERT_EQUAL_INT(5, ray.map_x);
	TEST_ASSERT_EQUAL_INT(5, ray.map_y);
}

/*
** Test 4: Vérifie init_ray avec un rayon vertical (dir_x = 0)
** delta_dist_x doit être très grand mais pas infini
*/
void	test_init_ray_vertical_ray(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 0.0, .dir_y = 1.0},
		.camera = {.plane_x = 0.66, .plane_y = 0.0}
	};
	t_ray	ray;

	init_ray(&ray, &game, SCREEN_WIDTH / 2);

	/* delta_dist_x doit être très grand (1e30) car dir_x ≈ 0 */
	TEST_ASSERT(ray.delta_dist_x > 1e20);
	TEST_ASSERT(ray.delta_dist_x != INFINITY);
}

/*
** Test 5: Vérifie init_ray avec un rayon horizontal (dir_y = 0)
** delta_dist_y doit être très grand mais pas infini
*/
void	test_init_ray_horizontal_ray(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 1.0, .dir_y = 0.0},
		.camera = {.plane_x = 0.0, .plane_y = 0.66}
	};
	t_ray	ray;

	init_ray(&ray, &game, SCREEN_WIDTH / 2);

	/* delta_dist_y doit être très grand (1e30) car dir_y ≈ 0 */
	TEST_ASSERT(ray.delta_dist_y > 1e20);
	TEST_ASSERT(ray.delta_dist_y != INFINITY);
}

/*
** Test 6: Vérifie init_dda_params avec des directions positives
** step doit être 1 et side_dist doit être calculé correctement
*/
void	test_init_dda_params_positive_dir(void)
{
	t_game	game = {.player = {.x = 5.5, .y = 5.3}};
	t_ray	ray = {
		.dir_x = 1.0,
		.dir_y = 1.0,
		.map_x = 5,
		.map_y = 5,
		.delta_dist_x = 1.0,
		.delta_dist_y = 1.0
	};

	init_dda_params(&ray, &game);

	/* Direction positive → step = 1 */
	TEST_ASSERT_EQUAL_INT(1, ray.step_x);
	TEST_ASSERT_EQUAL_INT(1, ray.step_y);
	/* side_dist = (map + 1 - player) * delta_dist */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.5, ray.side_dist_x);  /* 6.0 - 5.5 */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.7, ray.side_dist_y);  /* 6.0 - 5.3 */
}

/*
** Test 7: Vérifie init_dda_params avec des directions négatives
** step doit être -1 et side_dist doit être calculé correctement
*/
void	test_init_dda_params_negative_dir(void)
{
	t_game	game = {.player = {.x = 5.7, .y = 5.8}};
	t_ray	ray = {
		.dir_x = -1.0,
		.dir_y = -1.0,
		.map_x = 5,
		.map_y = 5,
		.delta_dist_x = 1.0,
		.delta_dist_y = 1.0
	};

	init_dda_params(&ray, &game);

	/* Direction négative → step = -1 */
	TEST_ASSERT_EQUAL_INT(-1, ray.step_x);
	TEST_ASSERT_EQUAL_INT(-1, ray.step_y);
	/* side_dist = (player - map) * delta_dist */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.7, ray.side_dist_x);  /* 5.7 - 5.0 */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.8, ray.side_dist_y);  /* 5.8 - 5.0 */
}

/*
** Test 8: Vérifie que delta_dist est calculé correctement
** delta_dist = |1 / dir|
*/
void	test_init_ray_delta_dist_calculation(void)
{
	t_game	game = {
		.player = {.x = 5.0, .y = 5.0, .dir_x = 0.5, .dir_y = 0.5},
		.camera = {.plane_x = 0.0, .plane_y = 0.0}
	};
	t_ray	ray;

	init_ray(&ray, &game, SCREEN_WIDTH / 2);

	/* delta_dist = |1 / 0.5| = 2.0 */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 2.0, ray.delta_dist_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, 2.0, ray.delta_dist_y);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_init_ray_left_column);
	RUN_TEST(test_init_ray_center_column);
	RUN_TEST(test_init_ray_right_column);
	RUN_TEST(test_init_ray_vertical_ray);
	RUN_TEST(test_init_ray_horizontal_ray);
	RUN_TEST(test_init_dda_params_positive_dir);
	RUN_TEST(test_init_dda_params_negative_dir);
	RUN_TEST(test_init_ray_delta_dist_calculation);
	/* Return failure count from Unity */
	return (UNITY_END());
}

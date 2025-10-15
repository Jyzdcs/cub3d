/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_camera_rotation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-15                              #+#    #+#             */
/*   Updated: 2025-10-15                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/controls_handler.h"
#include "../../include/cub3d.h"
#include "../Unity/src/unity.h"
#include <math.h>

static t_game	g_game;

/*
** Initialize game with standard facing east, FOV 66 degrees
*/
void	setUp(void)
{
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	g_game.camera.plane_x = 0.0;
	g_game.camera.plane_y = 0.66;
	g_game.player.rotation_speed = 0.1;
}

void	tearDown(void)
{
	/* No dynamic allocation to clean */
}

/*
** Test rotation 90 degrees: (1,0) -> (0,1)
*/
void	test_rotation_rotate_90_degrees_east_to_north(void)
{
	rotate_player(&g_game, M_PI / 2);
	/* Direction should be (0, 1) after 90° rotation */
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, g_game.player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 1.0, g_game.player.dir_y);
	/* Plane should be (-0.66, 0) */
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -0.66, g_game.camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, g_game.camera.plane_y);
}

/*
** Test rotation 180 degrees: reverses direction
*/
void	test_rotation_rotate_180_degrees_reverses_direction(void)
{
	rotate_player(&g_game, M_PI);
	/* Direction should be (-1, 0) after 180° rotation */
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -1.0, g_game.player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, g_game.player.dir_y);
	/* Plane should be (0, -0.66) */
	TEST_ASSERT_DOUBLE_WITHIN(0.001, 0.0, g_game.camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, -0.66, g_game.camera.plane_y);
}

/*
** Test rotation 360 degrees: returns to origin
*/
void	test_rotation_rotate_360_degrees_returns_to_origin(void)
{
	double	initial_dir_x;
	double	initial_dir_y;
	double	initial_plane_x;
	double	initial_plane_y;

	initial_dir_x = g_game.player.dir_x;
	initial_dir_y = g_game.player.dir_y;
	initial_plane_x = g_game.camera.plane_x;
	initial_plane_y = g_game.camera.plane_y;
	rotate_player(&g_game, 2 * M_PI);
	/* Should return to initial position */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_dir_x, g_game.player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_dir_y, g_game.player.dir_y);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_plane_x, g_game.camera.plane_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_plane_y, g_game.camera.plane_y);
}

/*
** Test rotate left then right cancels out
*/
void	test_rotation_rotate_left_then_right_cancels(void)
{
	double	initial_dir_x;
	double	initial_dir_y;

	initial_dir_x = g_game.player.dir_x;
	initial_dir_y = g_game.player.dir_y;
	rotate_left(&g_game);
	rotate_right(&g_game);
	/* Should return to initial direction */
	TEST_ASSERT_DOUBLE_WITHIN(0.0001, initial_dir_x, g_game.player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.0001, initial_dir_y, g_game.player.dir_y);
}

/*
** Test four 90-degree left rotations equal 360 degrees
*/
void	test_rotation_four_left_rotations_equals_360(void)
{
	double	initial_dir_x;
	double	initial_dir_y;

	g_game.player.rotation_speed = M_PI / 2;
	initial_dir_x = g_game.player.dir_x;
	initial_dir_y = g_game.player.dir_y;
	rotate_left(&g_game);
	rotate_left(&g_game);
	rotate_left(&g_game);
	rotate_left(&g_game);
	/* Should return to initial position after 4x90° */
	TEST_ASSERT_DOUBLE_WITHIN(0.001, initial_dir_x, g_game.player.dir_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.001, initial_dir_y, g_game.player.dir_y);
}

/*
** Test rotation preserves perpendicularity between dir and plane
*/
void	test_rotation_preserves_perpendicularity(void)
{
	double	dot_product;

	rotate_player(&g_game, 0.3);
	/* Dot product dir · plane should be 0 (perpendicular) */
	dot_product = g_game.player.dir_x * g_game.camera.plane_x
		+ g_game.player.dir_y * g_game.camera.plane_y;
	TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, dot_product);
}

/*
** Test rotation preserves plane magnitude
*/
void	test_rotation_preserves_plane_magnitude(void)
{
	double	initial_mag;
	double	final_mag;
	int		i;

	initial_mag = sqrt(g_game.camera.plane_x * g_game.camera.plane_x
			+ g_game.camera.plane_y * g_game.camera.plane_y);
	i = 0;
	while (i < 100)
	{
		rotate_player(&g_game, 0.05);
		i++;
	}
	final_mag = sqrt(g_game.camera.plane_x * g_game.camera.plane_x
			+ g_game.camera.plane_y * g_game.camera.plane_y);
	/* Magnitude should be preserved (within 1% tolerance) */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_mag, final_mag);
}

/*
** Test zero rotation speed causes no change
*/
void	test_rotation_zero_rotation_speed_no_change(void)
{
	double	initial_dir_x;
	double	initial_dir_y;

	g_game.player.rotation_speed = 0.0;
	initial_dir_x = g_game.player.dir_x;
	initial_dir_y = g_game.player.dir_y;
	rotate_left(&g_game);
	/* Should not move (rotation_speed = 0) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_dir_x, g_game.player.dir_x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_dir_y, g_game.player.dir_y);
}

/*
** Test large angle wraps correctly (modulo 2π)
*/
void	test_rotation_large_angle_wraps_correctly(void)
{
	double	result_large_x;
	double	result_large_y;
	double	result_zero_x;
	double	result_zero_y;

	/* Rotate by 10π (5 full rotations) */
	rotate_player(&g_game, 10 * M_PI);
	result_large_x = g_game.player.dir_x;
	result_large_y = g_game.player.dir_y;
	/* Reset and rotate by 0 (should be same as 10π modulo 2π) */
	setUp();
	rotate_player(&g_game, 0.0);
	result_zero_x = g_game.player.dir_x;
	result_zero_y = g_game.player.dir_y;
	/* 10π should be equivalent to 0 modulo 2π */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, result_zero_x, result_large_x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, result_zero_y, result_large_y);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_rotation_rotate_90_degrees_east_to_north);
	RUN_TEST(test_rotation_rotate_180_degrees_reverses_direction);
	RUN_TEST(test_rotation_rotate_360_degrees_returns_to_origin);
	RUN_TEST(test_rotation_rotate_left_then_right_cancels);
	RUN_TEST(test_rotation_four_left_rotations_equals_360);
	RUN_TEST(test_rotation_preserves_perpendicularity);
	RUN_TEST(test_rotation_preserves_plane_magnitude);
	RUN_TEST(test_rotation_zero_rotation_speed_no_change);
	RUN_TEST(test_rotation_large_angle_wraps_correctly);
	return (UNITY_END());
}


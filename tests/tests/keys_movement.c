/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-15                              #+#    #+#             */
/*   Updated: 2025-10-15                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/controls_handler.h"
#include "../../include/cub3d.h"
#include "../../include/map_parser.h"
#include "../Unity/src/unity.h"

static t_game	g_game;
static char		*g_map_data[] = {
	"111111",
	"100001",
	"100001",
	"100001",
	"100001",
	"111111",
	NULL
};

/*
** Initialize game with simple 6x6 map for testing
*/
void	setUp(void)
{
	g_game.map.map = g_map_data;
	g_game.map.width = 6;
	g_game.map.height = 6;
	g_game.player.x = 3.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	g_game.player.speed = 0.1;
}

void	tearDown(void)
{
	/* No dynamic allocation to clean */
}

/*
** Test collision detection: wall present
*/
void	test_movement_there_is_no_wall_detects_wall(void)
{
	int	result;

	/* Position at wall (0,0) with hitbox should detect wall */
	result = there_is_no_wall(&g_game.map, 0.5, 0.5);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/*
** Test collision detection: no wall (open space)
*/
void	test_movement_there_is_no_wall_detects_free_space(void)
{
	int	result;

	/* Center of map (3,3) should be free */
	result = there_is_no_wall(&g_game.map, 3.0, 3.0);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/*
** Test collision detection: edge case near wall
*/
void	test_movement_there_is_no_wall_near_wall_boundary(void)
{
	int	result;

	/* Just inside wall boundary with hitbox */
	result = there_is_no_wall(&g_game.map, 1.0 + HITBOX_SIZE + 0.01, 3.0);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/*
** Test forward movement: free space
*/
void	test_movement_move_forward_in_free_space(void)
{
	double	initial_x;
	double	initial_y;

	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	move_forward(&g_game);
	/* Should move in X direction (dir_x = 1.0) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x + 0.1, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y, g_game.player.y);
}

/*
** Test forward movement: blocked by wall
*/
void	test_movement_move_forward_blocked_by_wall(void)
{
	double	initial_x;

	/* Position near east wall, facing east */
	/* Wall at index 5, hitbox 0.2 → need x+0.2 >= 5 → x >= 4.8 */
	g_game.player.x = 4.78;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	initial_x = g_game.player.x;
	move_forward(&g_game);
	/* Should not move (wall at x=5) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
}

/*
** Test backward movement: free space
*/
void	test_movement_move_backward_in_free_space(void)
{
	double	initial_x;

	g_game.player.x = 3.0;
	g_game.player.dir_x = 1.0;
	initial_x = g_game.player.x;
	move_backward(&g_game);
	/* Should move opposite to dir_x */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x - 0.1, g_game.player.x);
}

/*
** Test backward movement: blocked by wall
*/
void	test_movement_move_backward_blocked_by_wall(void)
{
	double	initial_x;

	/* Position near west wall, facing east (backing into wall) */
	/* Wall at index 0, hitbox 0.2 → need x-0.2 <= 0 → x <= 0.2 */
	/* But wall at 1 is '0', so need to be near actual wall boundary */
	g_game.player.x = 1.1;
	g_game.player.dir_x = 1.0;
	initial_x = g_game.player.x;
	move_backward(&g_game);
	/* Should not move (wall at x=1) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
}

/*
** Test strafe left: free space
*/
void	test_movement_strafe_left_in_free_space(void)
{
	double	initial_x;
	double	initial_y;

	/* Facing east (1,0), strafe left should move north (0,-1) */
	g_game.player.x = 3.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	strafe_left(&g_game);
	/* X should not change, Y should decrease */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y + 0.1, g_game.player.y);
}

/*
** Test strafe right: free space
*/
void	test_movement_strafe_right_in_free_space(void)
{
	double	initial_x;
	double	initial_y;

	/* Facing east (1,0), strafe right should move south (0,1) */
	g_game.player.x = 3.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	strafe_right(&g_game);
	/* X should not change, Y should increase */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y - 0.1, g_game.player.y);
}

/*
** Test wall-slide: X blocked, Y free
*/
void	test_movement_wall_slide_x_blocked_y_free(void)
{
	double	initial_y;

	/* Near east wall, facing diagonally (will hit wall in X) */
	/* Wall at index 5, hitbox 0.2 → x >= 4.8 to detect collision */
	g_game.player.x = 4.78;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 1.0;
	initial_y = g_game.player.y;
	move_forward(&g_game);
	/* X blocked by wall, Y should still move */
	TEST_ASSERT_EQUAL_DOUBLE(4.78, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y + 0.1, g_game.player.y);
}

/*
** Test strafe left: blocked by wall
*/
void	test_movement_strafe_left_blocked_by_wall(void)
{
	double	initial_pos;

	/* Position near south wall, facing east, strafe left hits south */
	/* strafe_left with dir=(1,0) goes south: new_y = y + dir_x */
	/* Wall at y=5, hitbox 0.2 → y >= 4.8 to detect collision */
	g_game.player.x = 3.0;
	g_game.player.y = 4.78;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	initial_pos = g_game.player.y;
	strafe_left(&g_game);
	/* Should not move in Y (blocked by south wall) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_pos, g_game.player.y);
}

/*
** Test strafe right: blocked by wall
*/
void	test_movement_strafe_right_blocked_by_wall(void)
{
	double	initial_pos;

	/* Position near north wall, facing east, strafe right hits north */
	/* strafe_right with dir=(1,0) goes north: new_y = y - dir_x */
	/* Wall at y=0, hitbox 0.2 → y <= 0.2 to detect collision */
	g_game.player.x = 3.0;
	g_game.player.y = 1.1;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	initial_pos = g_game.player.y;
	strafe_right(&g_game);
	/* Should not move in Y (blocked by north wall) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_pos, g_game.player.y);
}

/*
** Test wall-slide: Y blocked, X free
*/
void	test_movement_wall_slide_y_blocked_x_free(void)
{
	double	initial_x;

	/* Near north wall, facing diagonally (will hit wall in Y) */
	/* Wall at y=0, need y far enough so X movement doesn't hit wall */
	/* Use y=2.0 so hitbox [1.8-2.2] won't reach wall at y=0 from X pos */
	g_game.player.x = 3.0;
	g_game.player.y = 1.2;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = -1.0;
	initial_x = g_game.player.x;
	move_forward(&g_game);
	/* Y blocked by wall, X should still move */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x + 0.1, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.2, g_game.player.y);
}

/*
** Test corner collision: both axes blocked
*/
void	test_movement_corner_collision_both_axes_blocked(void)
{
	double	initial_x;
	double	initial_y;

	/* Position in corner (NE), facing diagonally into corner */
	g_game.player.x = 4.78;
	g_game.player.y = 1.1;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = -1.0;
	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	move_forward(&g_game);
	/* Both axes blocked, no movement at all */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y, g_game.player.y);
}

/*
** Test movement with zero direction vector
*/
void	test_movement_with_zero_direction(void)
{
	double	initial_x;
	double	initial_y;

	/* Player with no direction */
	g_game.player.x = 3.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 0.0;
	g_game.player.dir_y = 0.0;
	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	move_forward(&g_game);
	/* Should not move (no direction) */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
	TEST_ASSERT_EQUAL_DOUBLE(initial_y, g_game.player.y);
}

/*
** Test movement with diagonal normalized direction
*/
void	test_movement_with_diagonal_direction(void)
{
	double	initial_x;
	double	initial_y;

	/* Player facing NE (normalized diagonal) */
	g_game.player.x = 3.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 0.707;
	g_game.player.dir_y = 0.707;
	g_game.player.speed = 0.1;
	initial_x = g_game.player.x;
	initial_y = g_game.player.y;
	move_forward(&g_game);
	/* Should move diagonally (both X and Y change) */
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_x + 0.0707, g_game.player.x);
	TEST_ASSERT_DOUBLE_WITHIN(0.01, initial_y + 0.0707, g_game.player.y);
}

/*
** Test exact boundary position (x.0)
*/
void	test_movement_exact_boundary_position(void)
{
	int	result;

	/* Player exactly at integer boundary */
	result = there_is_no_wall(&g_game.map, 5.0, 3.0);
	/* Wall at index 5, x=5.0 + 0.2 = 5.2 → (int)5.2 = 5 → wall */
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/*
** Test high speed does not skip walls
*/
void	test_movement_high_speed_does_not_skip_walls(void)
{
	double	initial_x;

	/* High speed near wall */
	g_game.player.x = 4.0;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	g_game.player.speed = 0.9;
	initial_x = g_game.player.x;
	move_forward(&g_game);
	/* new_x would be 4.9, wall at 5, hitbox reaches 5.1 → blocked */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
}

/*
** Test repeated blocked movement stays still
*/
void	test_movement_repeated_blocked_movement_stays_still(void)
{
	double	initial_x;
	int		i;

	/* Position against wall, try moving 100 times */
	g_game.player.x = 4.78;
	g_game.player.y = 3.0;
	g_game.player.dir_x = 1.0;
	g_game.player.dir_y = 0.0;
	g_game.player.speed = 0.1;
	initial_x = g_game.player.x;
	i = 0;
	while (i < 100)
	{
		move_forward(&g_game);
		i++;
	}
	/* Should remain at exact same position */
	TEST_ASSERT_EQUAL_DOUBLE(initial_x, g_game.player.x);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_movement_there_is_no_wall_detects_wall);
	RUN_TEST(test_movement_there_is_no_wall_detects_free_space);
	RUN_TEST(test_movement_there_is_no_wall_near_wall_boundary);
	RUN_TEST(test_movement_move_forward_in_free_space);
	RUN_TEST(test_movement_move_forward_blocked_by_wall);
	RUN_TEST(test_movement_move_backward_in_free_space);
	RUN_TEST(test_movement_move_backward_blocked_by_wall);
	RUN_TEST(test_movement_strafe_left_in_free_space);
	RUN_TEST(test_movement_strafe_right_in_free_space);
	RUN_TEST(test_movement_wall_slide_x_blocked_y_free);
	RUN_TEST(test_movement_strafe_left_blocked_by_wall);
	RUN_TEST(test_movement_strafe_right_blocked_by_wall);
	RUN_TEST(test_movement_wall_slide_y_blocked_x_free);
	RUN_TEST(test_movement_corner_collision_both_axes_blocked);
	RUN_TEST(test_movement_with_zero_direction);
	RUN_TEST(test_movement_with_diagonal_direction);
	RUN_TEST(test_movement_exact_boundary_position);
	RUN_TEST(test_movement_high_speed_does_not_skip_walls);
	RUN_TEST(test_movement_repeated_blocked_movement_stays_still);
	return (UNITY_END());
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:25:01 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/02 18:25:13 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/controls_handler.h"
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
** Test basic key press detection
*/
void test_key_press_basic(void)
{
	t_game game;
	game.keys.w_pressed = 0;

	int result = handle_key_press(XK_W, &game);

	TEST_ASSERT_EQUAL_INT(TRUE, result);
	TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);
}

/*
** Test key release detection
*/
void test_key_release_basic(void)
{
	t_game game;
	game.keys.w_pressed = 1;

	int result = handle_key_release(XK_W, &game);

	TEST_ASSERT_EQUAL_INT(TRUE, result);
	TEST_ASSERT_EQUAL_INT(0, game.keys.w_pressed);
}

/*
** Test movement keys (WASD)
*/
void test_movement_keys(void)
{
	t_game game;
	game.keys.w_pressed = 0;
	game.keys.a_pressed = 0;
	game.keys.s_pressed = 0;
	game.keys.d_pressed = 0;

	// Test W key (forward movement)
	handle_key_press(XK_W, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);

	// Test A key (left movement)
	handle_key_press(XK_A, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.a_pressed);

	// Test S key (backward movement)
	handle_key_press(XK_S, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.s_pressed);

	// Test D key (right movement)
	handle_key_press(XK_D, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.d_pressed);
}

/*
** Test rotation keys (arrow keys)
*/
void test_rotation_keys(void)
{
	t_game game;
	game.keys.left_pressed = 0;
	game.keys.right_pressed = 0;

	// Test left arrow key
	handle_key_press(XK_Left, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.left_pressed);

	// Test right arrow key
	handle_key_press(XK_Right, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.right_pressed);
}

/*
** Test escape key
*/
void test_escape_key(void)
{
	t_game game;
	game.keys.escape_pressed = 0;

	int result = handle_key_press(XK_Escape, &game);

	TEST_ASSERT_EQUAL_INT(FALSE, result);
	TEST_ASSERT_EQUAL_INT(1, game.keys.escape_pressed);
}

/*
** Test invalid key codes
*/
void test_invalid_key_codes(void)
{
	t_game game;
	int result = handle_key_press(999, &game); // Invalid key code
	TEST_ASSERT_EQUAL_INT(TRUE, result); // Should return TRUE for unknown keys
}

/*
** Test multiple key presses
*/
void test_multiple_key_presses(void)
{
	t_game game;

	// Test multiple consecutive key presses
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_W, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_A, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_S, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_D, &game));
}

/*
** Test key state management
*/
void test_key_state_management(void)
{
	t_game game;
	game.keys.w_pressed = 0;
	game.keys.a_pressed = 0;

	// Test that keys can be pressed and released properly
	handle_key_press(XK_W, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);

	handle_key_release(XK_W, &game);
	TEST_ASSERT_EQUAL_INT(0, game.keys.w_pressed);

	// Test multiple keys pressed simultaneously
	handle_key_press(XK_W, &game);
	handle_key_press(XK_A, &game);
	TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);
	TEST_ASSERT_EQUAL_INT(1, game.keys.a_pressed);
}

/*
** Test key input with game state
*/
void test_key_input_with_game_state(void)
{
	t_game game;
	game.keys.w_pressed = 0;
	game.keys.left_pressed = 0;
	game.keys.right_pressed = 0;

	// Test that keys update state properly
	handle_key_press(XK_W, &game);
	handle_key_press(XK_Left, &game);
	handle_key_press(XK_Right, &game);

	TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);
	TEST_ASSERT_EQUAL_INT(1, game.keys.left_pressed);
	TEST_ASSERT_EQUAL_INT(1, game.keys.right_pressed);
}

/*
** Test key input performance
*/
void test_key_input_performance(void)
{
	t_game game;
	game.keys.w_pressed = 0;

	// Test rapid key presses
	for (int i = 0; i < 100; i++)
	{
		handle_key_press(XK_W, &game);
		TEST_ASSERT_EQUAL_INT(1, game.keys.w_pressed);
		handle_key_release(XK_W, &game);
		TEST_ASSERT_EQUAL_INT(0, game.keys.w_pressed);
	}

	// Test escape still works after rapid presses
	int result = handle_key_press(XK_Escape, &game);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/*
** Main function to run all tests
*/
int main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();

	/* Run tests - add each test here */
	RUN_TEST(test_key_press_basic);
	RUN_TEST(test_key_release_basic);
	RUN_TEST(test_movement_keys);
	RUN_TEST(test_rotation_keys);
	RUN_TEST(test_escape_key);
	RUN_TEST(test_invalid_key_codes);
	RUN_TEST(test_multiple_key_presses);
	RUN_TEST(test_key_state_management);
	RUN_TEST(test_key_input_with_game_state);
	RUN_TEST(test_key_input_performance);

	/* Return failure count from Unity */
	return (UNITY_END());
}

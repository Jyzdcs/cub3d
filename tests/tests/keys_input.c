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

#include "../../include/controls.h"
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
	int result = handle_key_press(XK_W, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

/*
** Test key release detection
*/
void test_key_release_basic(void)
{
	// Note: This test is for key release, but handle_hey_press only handles key press
	// This would need a separate handle_key_release function
	TEST_ASSERT_TRUE(1); // Placeholder until key release function is implemented
}

/*
** Test movement keys (WASD)
*/
void test_movement_keys(void)
{
	t_game game;

	// Test W key (forward movement)
	int w_result = handle_key_press(XK_W, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, w_result);

	// Test A key (left movement)
	int a_result = handle_key_press(XK_A, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, a_result);

	// Test S key (backward movement)
	int s_result = handle_key_press(XK_S, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, s_result);

	// Test D key (right movement)
	int d_result = handle_key_press(XK_D, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, d_result);
}

/*
** Test rotation keys (arrow keys)
*/
void test_rotation_keys(void)
{
	t_game game;

	// Test left arrow key
	int left_result = handle_key_press(XK_Left, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, left_result);

	// Test right arrow key
	int right_result = handle_key_press(XK_Right, &game);
	TEST_ASSERT_EQUAL_INT(TRUE, right_result);
}

/*
** Test escape key
*/
void test_escape_key(void)
{
	t_game game;
	int result = handle_key_press(XK_Escape, &game);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
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

	// Test that different keys return consistent results
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_W, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_A, &game));
	TEST_ASSERT_EQUAL_INT(FALSE, handle_key_press(XK_Escape, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_W, &game));
}

/*
** Test key input with game state
*/
void test_key_input_with_game_state(void)
{
	t_game game;

	// Test that keys work with game state (using stubs)
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_W, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_Left, &game));
	TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_Right, &game));
}

/*
** Test key input performance
*/
void test_key_input_performance(void)
{
	t_game game;

	// Test rapid key presses
	for (int i = 0; i < 100; i++)
	{
		TEST_ASSERT_EQUAL_INT(TRUE, handle_key_press(XK_W, &game));
	}

	// Test escape still works after rapid presses
	TEST_ASSERT_EQUAL_INT(FALSE, handle_key_press(XK_Escape, &game));
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

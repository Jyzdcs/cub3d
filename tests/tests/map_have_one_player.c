/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_have_one_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unity-template                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-02                              #+#    #+#             */
/*   Updated: 2025-10-02                             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"
#include "../Unity/src/unity.h"

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
void	test_map_validation_have_one_player_valid(void)
{
	int		result;
	static char line0[] = "        1111111111111111111111111";
	static char line1[] = "        1000000000110000000000001";
	static char line2[] = "        1011000001110000000000001";
	static char line3[] = "        1001000000000000000000001";
	static char line4[] = "111111111011000001110000000000001";
	static char line5[] = "100000000011000001110111111111111";
	static char line6[] = "11110111111111011100000010001";
	static char line7[] = "11110111111111011101010010001";
	static char line8[] = "11000000110101011100000010001";
	static char line9[] = "10000000000000001100000010001";
	static char line10[] = "10000000000000001101010010001";
	static char line11[] = "11000001110101011111011110N0111";
	static char line12[] = "11110111 1110101 101111010001";
	static char line13[] = "11111111 1111111 111111111111";
	static char *map[] = {line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_map_validation_have_one_player_no_player(void)
{
	int		result;
	static char line0[] = "        1111111111111111111111111";
	static char line1[] = "        1000000000110000000000001";
	static char line2[] = "        1011000001110000000000001";
	static char line3[] = "        1001000000000000000000001";
	static char line4[] = "111111111011000001110000000000001";
	static char line5[] = "100000000011000001110111111111111";
	static char line6[] = "11110111111111011100000010001";
	static char line7[] = "11110111111111011101010010001";
	static char line8[] = "11000000110101011100000010001";
	static char line9[] = "10000000000000001100000010001";
	static char line10[] = "10000000000000001101010010001";
	static char line11[] = "11000001110101011111011110000111";
	static char line12[] = "11110111 1110101 101111010001";
	static char line13[] = "11111111 1111111 111111111111";
	static char *map[] = {line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_map_validation_have_one_player_multiple_players(void)
{
	int		result;
	static char line0[] = "        1111111111111111111111111";
	static char line1[] = "        1000000000110000000000001";
	static char line2[] = "        1011000001110000000000001";
	static char line3[] = "        1001000000000000000000001";
	static char line4[] = "111111111011000001110000000000001";
	static char line5[] = "100000000011000001110111111111111";
	static char line6[] = "11110111111111011100000010001";
	static char line7[] = "11110111111111011101010010001";
	static char line8[] = "110000001101010111000000S0001";
	static char line9[] = "10000000000000001100000010001";
	static char line10[] = "10000000000000001101010010001";
	static char line11[] = "11000001110101011111011110N0111";
	static char line12[] = "11110111 1110101 101111010001";
	static char line13[] = "11111111 1111111 111111111111";
	static char *map[] = {line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_map_validation_have_one_player_direction_N(void)
{
	int		result;
	static char line0[] = "1111";
	static char line1[] = "10N1";
	static char line2[] = "1111";
	static char *map[] = {line0, line1, line2, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_map_validation_have_one_player_direction_S(void)
{
	int		result;
	static char line0[] = "1111";
	static char line1[] = "10S1";
	static char line2[] = "1111";
	static char *map[] = {line0, line1, line2, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_map_validation_have_one_player_direction_E(void)
{
	int		result;
	static char line0[] = "1111";
	static char line1[] = "10E1";
	static char line2[] = "1111";
	static char *map[] = {line0, line1, line2, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_map_validation_have_one_player_direction_W(void)
{
	int		result;
	static char line0[] = "1111";
	static char line1[] = "10W1";
	static char line2[] = "1111";
	static char *map[] = {line0, line1, line2, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_map_validation_have_one_player_minimal_map(void)
{
	int		result;
	static char line0[] = "1111";
	static char line1[] = "10Y1";
	static char line2[] = "1111";
	static char *map[] = {line0, line1, line2, NULL};

	result = map_have_one_player(map);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

/*
** Main function to run all tests
*/
int	main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_map_validation_have_one_player_valid);
	RUN_TEST(test_map_validation_have_one_player_no_player);
	RUN_TEST(test_map_validation_have_one_player_multiple_players);
	RUN_TEST(test_map_validation_have_one_player_direction_N);
	RUN_TEST(test_map_validation_have_one_player_direction_S);
	RUN_TEST(test_map_validation_have_one_player_direction_E);
	RUN_TEST(test_map_validation_have_one_player_direction_W);
	RUN_TEST(test_map_validation_have_one_player_minimal_map);
	/* Return failure count from Unity */
	return (UNITY_END());
}

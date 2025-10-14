/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_map_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:25:01 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/14 12:40:23 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"
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

void	test_bad_extension_name(void)
{
	int	result;

	result = check_extension("map.txt", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_multilple_bad_extension(void)
{
	int	result;

	result = check_extension("map.cub.txt", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_with_bad_extension_and_good_extension(void)
{
	int	result;

	result = check_extension("map.txt.cub", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_with_null_param(void)
{
	int	result;

	result = check_extension(NULL, ".cub", 4);
	TEST_ASSERT_EQUAL_INT(FALSE, result);
}

void	test_with_right_extension(void)
{
	int	result;

	result = check_extension("map.cub", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_with_multiple_extensions(void)
{
	int	result;

	result = check_extension("map.cub.cub", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_with_minimum_file_name(void)
{
	int	result;

	result = check_extension("a.cub", ".cub", 4);
	TEST_ASSERT_EQUAL_INT(TRUE, result);
}

void	test_with_only_extension(void)
{
	int	result;

	result = check_extension(".cub", ".cub", 4);
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
	RUN_TEST(test_bad_extension_name);
	RUN_TEST(test_multilple_bad_extension);
	RUN_TEST(test_with_right_extension);
	RUN_TEST(test_with_null_param);
	RUN_TEST(test_with_multiple_extensions);
	RUN_TEST(test_with_minimum_file_name);
	RUN_TEST(test_with_only_extension);
	RUN_TEST(test_with_bad_extension_and_good_extension);
	/* Return failure count from Unity */
	return (UNITY_END());
}

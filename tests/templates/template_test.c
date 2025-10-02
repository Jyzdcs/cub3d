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
void	test_calculator_add_positive_numbers(void)
{
	int	result;

	/* Example function we might be testing */
	result = add(2, 3);
	/* Assertions - different types you might use */
	TEST_ASSERT_EQUAL_INT(5, result);
}

void	test_calculator_add_negative_numbers(void)
{
	int	result;

	result = add(-2, -3);
	TEST_ASSERT_EQUAL_INT(-5, result);
}

void	test_string_functions(void)
{
	char	str[10] = "Hello";
	int		array1[] = {1, 2, 3, 4};
	int		array2[] = {1, 2, 3, 4};

	/* Example string assertion */
	TEST_ASSERT_EQUAL_STRING("Hello", str);
	/* Example memory/array assertions */
	TEST_ASSERT_EQUAL_INT_ARRAY(array1, array2, 4);
}

void	test_null_checks(void)
{
	void	*ptr;

	ptr = NULL;
	/* Check for NULL */
	TEST_ASSERT_NULL(ptr);
	/* Example of checking that something is NOT null */
	ptr = malloc(5);
	if (ptr)
	{
		TEST_ASSERT_NOT_NULL(ptr);
		free(ptr);
	}
}

/*
** Main function to run all tests
*/
int	main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();
	/* Run tests - add each test here */
	RUN_TEST(test_calculator_add_positive_numbers);
	RUN_TEST(test_calculator_add_negative_numbers);
	RUN_TEST(test_string_functions);
	RUN_TEST(test_null_checks);
	/* Return failure count from Unity */
	return (UNITY_END());
}

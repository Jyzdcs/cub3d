#include "../../include/cub3d.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// Global test resources that need setup/cleanup

void setUp(void)
{
}

void tearDown(void)
{
}

void test_empty_file(void)
{
	typedef struct
	{
		char *file_path;
		char *message;
		int code;
	} test_case_t;

	test_case_t test_cases[] = {
			{"../maps/invalids/glsrkgnsl.cub", "Error: wrong path of map", FALSE},
			{"../maps/invalids/empty_map.cub", "Error: empty map", FALSE},
			{"../maps/valids/a.cub", NULL, TRUE},
	};

	for (unsigned long i = 0; i < sizeof(test_cases) / sizeof(test_case_t); i++)
	{
		int result = check_file_content(test_cases[i].file_path);
		TEST_ASSERT_EQUAL_INT_MESSAGE(test_cases[i].code, result, test_cases[i].message);
	};
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_empty_file);
	return (UNITY_END());
}
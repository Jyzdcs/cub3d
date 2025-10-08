#include "../../include/cub3d.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// Global test resources that need setup/cleanup
typedef struct
{
	char *file_path;
	char *message;
	int code;
} test_case_t;

t_game *game;

void setUp(void)
{
	game = malloc(sizeof(t_game));
	if (game)
		ft_memset(game, 0, sizeof(t_game));
}

void tearDown(void)
{
	if (game)
	{
		free(game);
		game = NULL;
	}
}

void test_multiple_case(void)
{
	test_case_t test_cases[] = {
			{"../maps/invalids/glsrkgnsl.cub", "MAP DONT EXIST !!!!!", FALSE},
			{"../maps/invalids/empty_map.cub", "EMPTY MAP !!!!!", FALSE},
			{"../maps/bad/map_first.cub", "MAP FIRST !!!!!", FALSE},
			{"../maps/bad/map_only.cub", "MAP ONLY !!!!!", FALSE},
			{"../maps/bad/textures_duplicates.cub", "textures duplicates", FALSE},
			{"../maps/bad/color_none.cub", "COLOR NONE !!!!!", FALSE},
			{"../maps/bad/textures_none.cub", "TEXTURES NONE !!!!!", FALSE},
			{"../maps/bad/textures_missing.cub", "TEXTURES MISSING !!!!!", FALSE},
			{"../maps/bad/textures_duplicates_2.cub", "4 TEXTURES WITH DUPLICATES !!!!!", FALSE},
			{"../maps/bad/textures_name_modified.cub", "TEXTURES NAME IS NORTH !!!!!", FALSE},
			// {"../maps/bad/custom.cub", "CUSTOM !!!!!", FALSE},
			// {"../maps/bad/map_missing.cub", "map missing", FALSE},
			// {"../maps/bad/file_letter_end.cub", "file letter end", FALSE},
			{"../maps/good/subject_map.cub", "MAP IS VALID !!!!!", TRUE},
	};

	for (unsigned long i = 0; i < sizeof(test_cases) / sizeof(test_case_t); i++)
	{
		int result = file_handler(test_cases[i].file_path, game);
		// printf("test : %s\n", test_cases[i].message);
		TEST_ASSERT_EQUAL_INT_MESSAGE(test_cases[i].code, result, test_cases[i].message);
	};
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_multiple_case);
	return (UNITY_END());
}
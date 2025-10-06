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
			{"../maps/invalids/glsrkgnsl.cub", "map dont exist", FALSE},
			{"../maps/invalids/empty_map.cub", "empty map", FALSE},
			// {"../maps/bad/color_invalid_rgb.cub", "color invalid rgb", FALSE},
			// {"../maps/bad/color_missing.cub", "color missing", FALSE},
			// {"../maps/bad/color_missing_ceiling_rgb.cub", "color missing ceiling rgb", FALSE},
			// {"../maps/bad/color_missing_floor_rgb.cub", "color missing floor rgb", FALSE},
			// {"../maps/bad/file_letter_end.cub", "file letter end", FALSE},
			{"../maps/bad/map_first.cub", "map first", FALSE},
			// {"../maps/bad/map_missing.cub", "map missing", FALSE},
			{"../maps/bad/map_only.cub", "map only", FALSE},
			// {"../maps/bad/textures_dir.cub", "textures dir", FALSE},
			// {"../maps/bad/textures_duplicates.cub", "textures duplicates", FALSE},
			// {"../maps/bad/textures_invalid.cub", "textures invalid", FALSE},
			// {"../maps/bad/textures_forbidden.cub", "textures forbidden", FALSE},
			// {"../maps/bad/textures_missing.cub", "textures missing", FALSE},
			// {"../maps/bad/textures_none.cub", "textures none", FALSE},
			// {"../maps/bad/textures_not_xpm.cub", "textures not xpm", FALSE},
			{"../maps/valids/a.cub", NULL, TRUE},
	};

	for (unsigned long i = 0; i < sizeof(test_cases) / sizeof(test_case_t); i++)
	{
		int result = file_handler(test_cases[i].file_path, game);
		TEST_ASSERT_EQUAL_INT_MESSAGE(test_cases[i].code, result, test_cases[i].message);
	};
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_multiple_case);
	return (UNITY_END());
}
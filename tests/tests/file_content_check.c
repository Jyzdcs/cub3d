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
			{"../maps/invalids/glsrkgnsl.cub", "wrong path of map", FALSE},
			{"../maps/invalids/empty_map.cub", "empty map", FALSE},
			{"../maps/bad/color_invalid_rgb.cub", "color invalid rgb", FALSE},
			{"../maps/bad/color_missing.cub", "color missing", FALSE},
			{"../maps/bad/color_missing_ceiling_rgb.cub", "color missing ceiling rgb", FALSE},
			{"../maps/bad/color_missing_floor_rgb.cub", "color missing floor rgb", FALSE},
			{"../maps/bad/file_letter_end.cub", "file letter end", FALSE},
			{"../maps/bad/map_first.cub", "map first", FALSE},
			{"../maps/bad/map_missing.cub", "map missing", FALSE},
			{"../maps/bad/map_only.cub", "map only", FALSE},
			{"../maps/bad/textures_dir.cub", "textures dir", FALSE},
			{"../maps/bad/textures_duplicates.cub", "textures duplicates", FALSE},
			{"../maps/bad/textures_invalid.cub", "textures invalid", FALSE},
			{"../maps/bad/textures_forbidden.cub", "textures forbidden", FALSE},
			{"../maps/bad/textures_missing.cub", "textures missing", FALSE},
			{"../maps/bad/textures_none.cub", "textures none", FALSE},
			{"../maps/bad/textures_not_xpm.cub", "textures not xpm", FALSE},
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
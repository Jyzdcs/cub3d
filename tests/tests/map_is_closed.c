/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:25:01 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/30 13:51:45 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"
#include "../../include/cub3d.h"
#include "../Unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>
/*
** This is run before EACH test, not just once for the whole test suite
*/
void setUp(void)
{
}

/*
** This is run after EACH test, not just once for the whole test suite
*/
void tearDown(void)
{
}

void test_map_is_closed_basic(void)
{
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
	static char *map_copy[] = {line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, NULL};

	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 33;	 // longueur de la ligne la plus longue
	map.height = 14; // nombre de lignes
	map.is_closed = 0;

	player.x = 29; // Position du 'N' dans la ligne 11
	player.y = 11; // Ligne 11 (index 11)
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide)
}

void test_map_is_closed_angle_internal(void)
{
	char *map_copy[] = {
			"        1111111111111111111111111",
			"        1000000000110000000000001",
			"        1011000001110000000000001",
			"        1001000000000000000000001",
			"111111111011000001110000000000001",
			"100000000011000001110111111111111",
			"11110111111111011100000010001",
			"11110111111111011101010010001",
			"11000000110101011100000010001",
			"10000000000000001100000010001",
			"10000000000000001101010010001",
			"11000001110101011111011110N0111",
			"11110111 1110101 101111010001",
			"11111111 1111111 11111111111", // Manque un '1' à la fin
			NULL};
	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 32; // ligne plus courte (manque un caractère)
	map.height = 14;
	map.is_closed = 0;

	player.x = 29; // Position du 'N' dans la ligne 11
	player.y = 11; // Ligne 11 (index 11)
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide)
}

void test_map_is_closed_angle_internal2(void)
{
	char *map_copy[] = {
			"1111111111111111111111111",
			"1000000000110000000000001",
			"1011000001110000000000001",
			"1001000000000000000000001",
			"111111111011000001110000000000001",
			"100000000011000001110111111111111",
			"11110111111111011100000010001",
			"11110111111111011101010010001",
			"11000000110101011100000010001",
			"10000000000000001100000010001",
			"10000000000000001101010010001",
			"11000001110101011111011110N0111",
			"11110111 1110101 101111010001",
			"111111110111111111111111111", // Trou dans le mur (0 au lieu de 1) - crée un angle interne
			NULL};
	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 33;
	map.height = 14;
	map.is_closed = 0;

	player.x = 29; // Position du 'N' dans la ligne 11
	player.y = 11; // Ligne 11 (index 11)
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide)
}

void test_map_is_closed_minimal_valid_map(void)
{
	static char line0[] = "1111";
	static char line1[] = "10N1"; // ← Modifiable ET stable en mémoire
	static char line2[] = "1111";
	static char *map_copy[] = {line0, line1, line2, NULL};

	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 4;
	map.height = 3;
	map.is_closed = 0;

	player.x = 2; // Position du joueur 'N' dans "10N1"
	player.y = 1; // Ligne 1 (index 1)
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide)
}

void test_map_is_closed_player_outside_map(void)
{
	char *map_copy[] = {
			"1111111111111111111111111",
			"1000000000110000000000001",
			"1011000001110000000000001",
			"1001000000000000000000001",
			"111111111011000001110000000000001",
			"100000000011000001110111111111111",
			"11110111111111011100000010001",
			"11110111111111011101010010001",
			"11000000110101011100000010001",
			"10000000000000001100000010001",
			"10000000000000001101010010001",
			"11000001110101011111011110N0111",
			"11110111 1110101 101111010001",
			"11111111 1111111 111111111111",
			NULL};
	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 33;
	map.height = 14;
	map.is_closed = 0;

	player.x = 50; // Position en dehors de la map
	player.y = 50;
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(1, result); // Map ouverte = 1 (invalide)
}

void test_map_is_closed_truly_open_map(void)
{
	static char line0[] = "1111111111111111111111111";
	static char line1[] = "1000000000110000000000001";
	static char line2[] = "1011000001110000000000001";
	static char line3[] = "1001000000000000000000001";
	static char line4[] = "111111111011000001110000000000001";
	static char line5[] = "100000000011000001110111111111111";
	static char line6[] = "11110111111111011100000010001";
	static char line7[] = "11110111111111011101010010001";
	static char line8[] = "11000000110101011100000010001";
	static char line9[] = "10000000000000001100000010001";
	static char line10[] = "10000000000000001101010010001";
	static char line11[] = "11000001110101011111011110N0111";
	static char line12[] = "11110111 1110101 101111010001";
	static char line13[] = "11111111 1111111 1111111111110"; // Trou à la fin - mais joueur dans zone fermée
	static char *map_copy[] = {line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, NULL};

	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 33;
	map.height = 14;
	map.is_closed = 0;

	player.x = 29; // Position du 'N' dans la ligne 11
	player.y = 11; // Ligne 11 (index 11)
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide) - joueur ne peut pas sortir
}

void test_map_is_closed_empty_map(void)
{
	static char *map_copy[] = {NULL};

	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 0;
	map.height = 0;
	map.is_closed = 0;

	player.x = 0;
	player.y = 0;
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(1, result); // Map vide = 1 (invalide)
}

void test_map_is_closed_single_wall(void)
{
	static char line0[] = "1111";
	static char *map_copy[] = {line0, NULL};
	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 4;
	map.height = 1;
	map.is_closed = 0;

	player.x = 1; // Position dans le mur
	player.y = 0;
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(0, result); // Map fermée = 0 (valide) - pas de sortie possible
}

void test_map_with_single_line_and_player_placed(void)
{
	static char line0[] = "11S1";
	static char *map_copy[] = {line0, NULL};

	t_map map;
	t_player player;

	// Initialiser les dimensions et l'état de la map
	map.width = 4;
	map.height = 1;
	map.is_closed = 0;

	player.x = 2; // Position dans le mur
	player.y = 0;
	map.map = (char **)map_copy;
	int result = map_is_closed(&map, &player);
	TEST_ASSERT_EQUAL_INT(FALSE, result); // Map fermée = 0 (valide) - pas de sortie possible
}

/*
** Main function to run all tests
*/
int main(void)
{
	/* Initialize Unity */
	UNITY_BEGIN();

	/* Run tests - add each test here */
	RUN_TEST(test_map_is_closed_basic);
	RUN_TEST(test_map_is_closed_angle_internal);
	RUN_TEST(test_map_is_closed_angle_internal2);
	RUN_TEST(test_map_is_closed_player_outside_map);
	RUN_TEST(test_map_is_closed_minimal_valid_map);
	RUN_TEST(test_map_is_closed_truly_open_map);
	RUN_TEST(test_map_is_closed_empty_map);
	RUN_TEST(test_map_is_closed_single_wall);
	RUN_TEST(test_map_with_single_line_and_player_placed);
	/* Return failure count from Unity */
	return (UNITY_END());
}

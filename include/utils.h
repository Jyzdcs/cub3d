/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:44 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/06 14:48:01 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"
#include <fcntl.h>

#define TRUE 0
#define FALSE 1

typedef struct s_game t_game;

void exit_game(t_game *game, char *message);
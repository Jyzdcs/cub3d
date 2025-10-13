/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:41:44 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/13 14:32:26 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define TRUE 0
# define FALSE 1
# include "../libs/libft/libft.h"
# include <fcntl.h>

typedef struct s_game	t_game;

void					exit_game(t_game *game, char *message);

#endif
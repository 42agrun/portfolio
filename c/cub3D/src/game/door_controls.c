/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_controls_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:21:14 by lbaumann          #+#    #+#             */
/*   Updated: 2023/08/30 12:51:48 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#include "../../inc/math_framework.h"
#include "../../libft/includes/libft.h"
#include "../../inc/line.h"

/*	2 = door has been closed | 3 = door has been opened			*/

static void	interact_door(t_game *game, t_vector door, bool is_open)
{
	if (is_open)
	{
		game->map[(int)door.y][(int)door.x] = 2;
	}
	else
	{
		game->map[(int)door.y][(int)door.x] = 3;
	}
}

bool	check_door(t_game *game)
{
	t_vector	door;

	door = add_vec(game->pos, game->dir);
	if ((int)(door.x) <= game->width && (int)(door.y) <= game->height
		&& (game->map[(int)door.y][(int)door.x] == 2
		|| game->map[(int)door.y][(int)door.x] == 3))
	{
		if (game->map[(int)door.y][(int)door.x] == 2)
			interact_door(game, door, false);
		else
			interact_door(game, door, true);
		return (true);
	}
	return (false);
}

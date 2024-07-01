/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:36:20 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/04 16:42:40 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	move_fwd(t_game *game)
{
	t_vector	new_pos;

	new_pos = add_vec(game->pos, scale_vec(game->dir, PLAYER_SPEED_MOV));
	if (no_collision(game, new_pos))
		game->pos = new_pos;
}

void	move_bwd(t_game *game)
{
	t_vector	new_pos;

	new_pos = sub_vec(game->pos, scale_vec(game->dir, PLAYER_SPEED_MOV));
	if (no_collision(game, new_pos))
		game->pos = new_pos;
}

/**
 * rotate dir by 90 degrees (pi / 2 in radian) to move left right
*/
void	move_left(t_game *game)
{
	t_vector	rotated_dir;
	t_vector	new_pos;

	rotated_dir = rotate_vec(game->dir, M_PI / 2);
	new_pos = sub_vec(game->pos, scale_vec(rotated_dir, PLAYER_SPEED_MOV));
	if (no_collision(game, new_pos))
		game->pos = new_pos;
}

void	move_right(t_game *game)
{
	t_vector	rotated_dir;
	t_vector	new_pos;

	rotated_dir = rotate_vec(game->dir, M_PI / 2);
	new_pos = add_vec(game->pos, scale_vec(rotated_dir, PLAYER_SPEED_MOV));
	if (no_collision(game, new_pos))
		game->pos = new_pos;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:47:51 by agrun             #+#    #+#             */
/*   Updated: 2023/08/16 12:47:57 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../inc/math_framework.h"

static bool	valid_move(t_game *game, t_vector new_pos)
{
	if ((int)(new_pos.x) <= game->width && (int)(new_pos.y) <= game->height
		&& (int)(new_pos.x) > 0 && (int)(new_pos.y) > 0
		&& (game->map[(int)new_pos.y][(int)new_pos.x] == 0
		|| (BONUS == 1 && game->map[(int)new_pos.y][(int)new_pos.x] == 3)))
	{
		return (true);
	}
	return (false);
}

bool	no_collision(t_game *game, t_vector new_pos)
{
	if (!valid_move(game, create_vec(new_pos.x, new_pos.y + MIN_WALL_DIST)))
		return (false);
	if (!valid_move(game, create_vec(new_pos.x, new_pos.y - MIN_WALL_DIST)))
		return (false);
	if (!valid_move(game, create_vec(new_pos.x - MIN_WALL_DIST, new_pos.y)))
		return (false);
	if (!valid_move(game, create_vec(new_pos.x + MIN_WALL_DIST, new_pos.y)))
		return (false);
	return (true);
}

void	rotate_left(t_game *game)
{
	game->dir = rotate_vec(game->dir, -PLAYER_SPEED_ROT);
	game->plane = rotate_vec(game->plane, -PLAYER_SPEED_ROT);
}

void	rotate_right(t_game *game)
{
	game->dir = rotate_vec(game->dir, PLAYER_SPEED_ROT);
	game->plane = rotate_vec(game->plane, PLAYER_SPEED_ROT);
}

/*	The very first condition checks for the ESC-key to close the game with.
	
	The game is supposed to support WASD for movement and LEFT and RIGHT
	arrowkeys for turning the camera/player point of view.			*/

int	key_press(int keycode, t_root *root)
{
	if (keycode == MLX_ESC)
		root_destroy(root, 0);
	if (keycode == MLX_W)
		move_fwd(root->game);
	if (keycode == MLX_S)
		move_bwd(root->game);
	if (keycode == MLX_A)
		move_left(root->game);
	if (keycode == MLX_D)
		move_right(root->game);
	if (BONUS == 1 && keycode == MLX_E)
		check_door(root->game);
	if (keycode == MLX_ARROW_L)
		rotate_left(root->game);
	if (keycode == MLX_ARROW_R)
		rotate_right(root->game);
	return (0);
}

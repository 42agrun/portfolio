/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:09:50 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 11:50:15 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

/**
 * camera_scalar: scalar to scale plane according to actual screen size
 * 1 on the right side and -1 on the left side
*/
void	get_ray_dir(t_game *game, int x)
{
	float	camera_scalar;

	camera_scalar = (2 * x / (float)(WIN_WIDTH - 1)) - 1;
	game->ray_dir = add_vec(game->dir, scale_vec(game->plane, camera_scalar));
}

/**
 * derived from pythagoras with ray_dir vector and 1 (because step in one
 * direction is one)
 * 
 * 1 is used instead of |ray_dir| because only ratio between delta_grid x and y
 * is important later
*/
void	get_delta_grid(t_game *game)
{
	assign_vec(&game->delta_grid,
		fabsf(1 / game->ray_dir.x), fabsf(1 / game->ray_dir.y));
}

void	get_side_dist(t_game *game)
{
	if (game->ray_dir.x < 0)
	{
		game->step.x = -1;
		game->side_dist.x = (game->pos.x - game->map_pos.x)
			* game->delta_grid.x;
	}
	else
	{
		game->step.x = 1;
		game->side_dist.x = (game->map_pos.x + 1 - game->pos.x)
			* game->delta_grid.x; 
	}
	if (game->ray_dir.y < 0)
	{
		game->step.y = -1;
		game->side_dist.y = (game->pos.y - game->map_pos.y)
			* game->delta_grid.y;
	}
	else
	{
		game->step.y = 1;
		game->side_dist.y = (game->map_pos.y + 1 - game->pos.y)
			* game->delta_grid.y; 
	}
}

void	get_dist(t_game *game)
{
	if (!game->side)
		game->ortho_wall_dist = (game->side_dist.x - game->delta_grid.x);
	else
		game->ortho_wall_dist = (game->side_dist.y - game->delta_grid.y);
}

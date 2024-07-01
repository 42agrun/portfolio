/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:30:35 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 11:29:59 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	generate_minimap(t_img *minimap, t_game *game)
{
	int			x_temp;
	t_vec_int	px;
	t_vector	minimap_pos;

	assign_vec_int(&px, 0, 0);
	assign_vec(&minimap_pos, 0, 0);
	x_temp = minimap_pos.x;
	while (px.y <= game->height)
	{
		px.x = 0;
		minimap_pos.x = x_temp;
		while (px.x <= game->width)
		{
			if (game->map[px.y][px.x] == 1)
				draw_square(minimap, minimap_pos, MINIMAP_TILE_SZ, PURPLE);
			else if (game->map[px.y][px.x] == 2)
				draw_square(minimap, minimap_pos, MINIMAP_TILE_SZ, BROWN);
			else
				draw_square(minimap, minimap_pos, MINIMAP_TILE_SZ, BLACK);
			minimap_pos.x += MINIMAP_TILE_SZ;
			px.x++;
		}
		minimap_pos.y += MINIMAP_TILE_SZ;
		px.y++;
	}
}

static void	draw_player(t_game *game, t_img *mlx_img)
{
	t_vector	center;
	int			i;
	float		scale;

	assign_vec(&center,
		(MM_X + MINIMAP_SZ / 2),
		(MM_Y + MINIMAP_SZ / 2));
	i = 0;
	while (i < WIN_WIDTH)
	{
		scale = game->minimap_rays_dist[i] * MINIMAP_TILE_SZ;
		if (scale > 0.4 * MINIMAP_SZ)
			scale = 0.4 * MINIMAP_SZ;
		visualize_vec(mlx_img, center, game->minimap_rays[i], scale);
		i++;
	}
	center.x -= MINIMAP_PLAYER_SIZE / 2;
	center.y -= MINIMAP_PLAYER_SIZE / 2;
	draw_square(mlx_img, center, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
}

static void	draw_minimap(t_img *mlx_img, t_img *minimap, t_vector offset)
{
	t_vec_int	px;
	int			x_start;
	int			*img_data;

	assign_vec_int(&px, 0, 0);
	img_data = (int *)minimap->data;
	x_start = offset.x;
	while (px.y < MINIMAP_SZ)
	{
		px.x = 0;
		offset.x = x_start;
		while (px.x < MINIMAP_SZ)
		{
			if (offset.x >= 0 && offset.y >= 0
				&& offset.x < minimap->width && offset.y < minimap->height)
				mlx_put_pixel_img(mlx_img, MM_X + px.x, MM_Y + px.y,
					img_data[(int)offset.y * minimap->width + (int)offset.x]);
			else
				mlx_put_pixel_img(mlx_img, MM_X + px.x, MM_Y + px.y, BLACK);
			px.x++;
			offset.x++;
		}
		px.y++;
		offset.y++;
	}
}

void	display_minimap(t_root *root, t_game *game)
{
	t_vector	minimap_origin;
	t_vector	player_pos_minimap;
	t_vector	offset;

	assign_vec(&minimap_origin, MM_X, MM_Y);
	player_pos_minimap = game->pos;
	player_pos_minimap = scale_vec(player_pos_minimap, (float)MINIMAP_TILE_SZ);
	offset = player_pos_minimap;
	offset.x = player_pos_minimap.x - (float)(MINIMAP_SZ / 2);
	offset.y = player_pos_minimap.y - (float)(MINIMAP_SZ / 2);
	draw_minimap(root->mlx_img, root->minimap, offset);
	draw_player(game, root->mlx_img);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:21:14 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 11:34:58 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	step_until_wall(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta_grid.x;
			game->map_pos.x += game->step.x;
			game->side = false;
		}
		else
		{
			game->side_dist.y += game->delta_grid.y;
			game->map_pos.y += game->step.y;
			game->side = true;
		}
		if (game->map[game->map_pos.y][game->map_pos.x] == 1
			|| game->map[game->map_pos.y][game->map_pos.x] == 2)
			hit = 1;
	}
}

void	draw_wall(t_root *root, t_vector start, t_vector end, int height_column)
{
	int			*img_data;
	t_img		*texture;
	int			offset;
	t_vec_int	tex_vec;
	int			color;

	offset = start.y;
	start.y -= offset;
	end.y -= offset;
	texture = select_texture(root, root->game);
	tex_vec.x = get_x_texture(root->game, texture);
	img_data = (int *)texture->data;
	while (start.y <= end.y)
	{
		tex_vec.y = get_y_texture(start.y, height_column, texture);
		color = img_data[tex_vec.y * texture->width + tex_vec.x];
		if (color == (int)0xFF000000)
			color = get_background(root, root->game, height_column, start.y);
		mlx_put_pixel_img(root->mlx_img, start.x, start.y + offset,
			adjust_lighting(color, height_column));
		start.y++;
	}
}

void	draw_column(t_root *root, int x, int height_column)
{
	int			wall_start;
	int			wall_end;
	t_vector	start;
	t_vector	end;

	wall_start = (int)((WIN_HEIGHT - height_column) / 2);
	wall_end = wall_start + height_column;
	assign_vec(&start, x, 0);
	assign_vec(&end, x, wall_start);
	plot_line(start, end, root->rgb_c, root->mlx_img);
	assign_vec(&start, x, wall_start);
	assign_vec(&end, x, wall_end);
	draw_wall(root, start, end, height_column);
	assign_vec(&start, x, wall_end);
	assign_vec(&end, x, WIN_HEIGHT);
	plot_line(start, end, root->rgb_f, root->mlx_img);
}

void	save_minimaps_rays(t_game *game, int i)
{
	game->minimap_rays[i] = game->ray_dir;
	game->minimap_rays_dist[i] = game->ortho_wall_dist;
}

/**   0 1 2 3 4 5 6 7
 *  ------------------>x  $: vertical wall at x = 5   -> if hit: side = 0
 * 0| * * * * * $ * *	  #: horizontal wall at y = 3 -> if hit: side = 1
 * 1| * * * * * $ * *
 * 2| * * * * * $ * *
 * 3| # # # # # $ # #
 * 4| * * * * * $ * *
 * 5| * * * * * $ * *
 *  v
 * y
*/
void	iterate_width(t_root *root, t_game *game)
{
	int		x;
	int		height_column;

	x = 0;
	while (x < WIN_WIDTH)
	{
		game->map_pos.x = (int)game->pos.x;
		game->map_pos.y = (int)game->pos.y;
		get_ray_dir(game, x);
		get_delta_grid(game);
		get_side_dist(game);
		step_until_wall(game);
		get_dist(game);
		height_column = (int)((float)WIN_HEIGHT / game->ortho_wall_dist);
		draw_column(root, x, height_column);
		save_minimaps_rays(game, x);
		x++;
	}
}

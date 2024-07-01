/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:06:33 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/05 16:54:05 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

/**
 * x_texture is the x value that is used to select which pixel column from
 * the texture should be selected
 * 
 * it is the point where the ray hits the wall
 * 
 * game->side == 1: horizontal wall hit, therefore x component
 * 
 * wall_hit: get only decimal part
*/
int	get_x_texture(t_game *game, t_img *texture)
{
	float	wall_hit;
	int		x_texture;

	if (game->side == 1)
		wall_hit = game->pos.x + game->ray_dir.x * game->ortho_wall_dist;
	else
		wall_hit = game->pos.y + game->ray_dir.y * game->ortho_wall_dist;
	wall_hit = wall_hit - (int)wall_hit;
	x_texture = (int)(texture->width * wall_hit);
	return (x_texture);
}

/**
 * step_size is the factor to multiply y to get the correct y_texture
 * coordinate
 * 1		2
 * | 		|			texture->height = 4
 * |		|			wall 1: step_size = 2 -> pixels are skipped
 * 			|			wall 2: step_size = 0.5 -> pixels are drawn twice
 * 			|	
 * 			|
 * 			|
 * 			|
*/
int	get_y_texture(int y, int height_column, t_img *texture)
{
	float	step_size;
	int		y_texture;

	step_size = texture->height / (float)height_column;
	y_texture = (int)(step_size * (float)y);
	return (y_texture);
}

t_img	*select_texture(t_root *root, t_game *game)
{
	if (game->map[game->map_pos.y][game->map_pos.x] == 2)
		return (root->door);
	else if (!game->side && game->ray_dir.x < 0)
	{
		if (game->map[game->map_pos.y][game->map_pos.x + 1] == 3)
			return (root->door_open);
		return (root->wall_we);
	}
	else if (!game->side && game->ray_dir.x > 0)
	{
		if (game->map[game->map_pos.y][game->map_pos.x - 1] == 3)
			return (root->door_open);
		return (root->wall_ea);
	}
	else if (game->side && game->ray_dir.y > 0)
	{
		if (game->map[game->map_pos.y - 1][game->map_pos.x] == 3)
			return (root->door_open);
		return (root->wall_so);
	}
	if (game->map[game->map_pos.y + 1][game->map_pos.x] == 3)
		return (root->door_open);
	return (root->wall_no);
}

int	get_background(t_root *root, t_game *game, int height_column, int y)
{
	t_img		*texture;
	t_vec_int	tex_vec;
	int			*img_data;

	if (!game->side && game->ray_dir.x < 0)
		texture = root->wall_we;
	else if (!game->side && game->ray_dir.x > 0)
		texture = root->wall_ea;
	else if (game->side && game->ray_dir.y > 0)
		texture = root->wall_so;
	else
		texture = root->wall_no;
	tex_vec.x = get_x_texture(root->game, texture);
	tex_vec.y = get_y_texture(y, height_column, texture);
	img_data = (int *)texture->data;
	return (img_data[tex_vec.y * texture->width + tex_vec.x]);
}

int	adjust_lighting(int color, int height_column)
{
	int		r;
	int		g;
	int		b;
	float	lighting_scalar;

	mlx_int_to_rgb(color, &r, &g, &b);
	lighting_scalar = (float)height_column / (float)WIN_HEIGHT;
	if (lighting_scalar > 1)
		lighting_scalar = 1;
	r *= lighting_scalar;
	g *= lighting_scalar;
	b *= lighting_scalar;
	return (mlx_rgb_to_int(0, r, g, b));
}

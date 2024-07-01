/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:14:00 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/06 15:02:11 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3D.h"
# include "math_framework.h"
# include "line.h"

/*
	texture.c
*/
int		get_x_texture(t_game *game, t_img *texture);
int		get_y_texture(int y, int height_column, t_img *texture);
t_img	*select_texture(t_root *root, t_game *game);
int		adjust_lighting(int color, int height_column);
int		get_background(t_root *root, t_game *game, int height_column, int y);

/*
	raycast_setup.c
*/
void	get_ray_dir(t_game *game, int x);
void	get_delta_grid(t_game *game);
void	get_side_dist(t_game *game);
void	get_dist(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:27:07 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/06 15:04:30 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

/*
	MINIMAP_TILE_SIZE = MINIMAP_SZ / MINIMAP_N_TILES
*/
# define MINIMAP_SZ 150
# define MINIMAP_N_TILES 10
# define MINIMAP_TILE_SZ 15
# define MM_X 0
# define MM_Y 0
# define MINIMAP_PLAYER_SIZE 5
# define MINIMAP_PLAYER_COLOR YELLOW
# define MINIMAP_RAY_CLR LIGHT_BLUE

# include "cub3D.h"
# include "line.h"
# include "math_framework.h"

/*
	minimap_helper.c
*/
void	visualize_vec(t_img *mlx_img, t_vector v1, t_vector v2, float lambda);
void	draw_square(t_img *mlx_img, t_vector pos, int size, int color);

#endif

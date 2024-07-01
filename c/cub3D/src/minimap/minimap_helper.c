/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:39:46 by lbaumann          #+#    #+#             */
/*   Updated: 2023/09/04 09:48:03 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minimap.h"

void	visualize_vec(t_img *mlx_img, t_vector v1, t_vector v2, float lambda)
{
	v2 = scale_vec(v2, lambda);
	v2 = add_vec(v1, v2);
	plot_line(v1, v2, MINIMAP_RAY_CLR, mlx_img);
}

void	draw_square(t_img *mlx_img, t_vector pos, int size, int color)
{
	int	x_temp;
	int	y_temp;

	x_temp = (int)pos.x;
	y_temp = (int)pos.y;
	while (y_temp < pos.y + size)
	{
		pos.x = x_temp;
		while (pos.x < x_temp + size)
		{
			mlx_put_pixel_img(mlx_img, (int)pos.x, y_temp, color);
			pos.x++;
		}
		y_temp++;
	}
}

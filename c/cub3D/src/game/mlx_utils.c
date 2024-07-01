/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/09/04 09:07:37 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	mlx_put_pixel_img(t_img *mlx_img, int x, int y, int color)
{
	int	*img_data;

	if (!mlx_img)
		return ;
	if (x >= mlx_img->width || y >= mlx_img->height || x < 0 || y < 0)
		return ;
	img_data = (int *)mlx_img->data;
	img_data[y * mlx_img->width + x] = color;
}

unsigned int	mlx_rgb_to_int(int o, int r, int g, int b)
{
	return (o << 24 | r << 16 | g << 8 | b);
}

void	mlx_int_to_rgb(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = (color) & 0xFF;
}

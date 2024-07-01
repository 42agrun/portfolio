/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:20:10 by lbaumann          #+#    #+#             */
/*   Updated: 2023/08/29 15:23:22 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#include "../../inc/line.h"

/**
 * Mallocs memory for Bresenham struct and assigns all the values necessary
 * for the Bresenham line algorithm
 * @param p1 starting point p1(x1,y1)
 * @param p2 end point p2(x2,y2)
 * @param line pointer to Bresenham struct
 * @return NULL if allocations fails OR pointer to allocated Bresenham struct
*/
void	init_line(t_vector p1, t_vector p2, t_bresenham *line)
{
	line->dx = abs((int)p2.x - (int)p1.x);
	line->dy = -abs((int)p2.y - (int)p1.y);
	line->err = line->dx + line->dy;
	line->x = (int)p1.x;
	line->y = (int)p1.y;
	if (p1.x > p2.x)
		line->sx = -1;
	else
		line->sx = 1;
	if (p1.y > p2.y)
		line->sy = -1;
	else
		line->sy = 1;
}

/**
 * Draws a line on the mlx_image from p1 to p2. First Bresenham struct
 * is assigned via init_line function (freed in the end of function).
 * Positive error value indicates deviation to implicit function to one
 * side, negative to the other side. There are always three possible
 * candidates for the next pixel: (x+1)(y), (x)(y+1), (x+1)(y+1).
 * Error value is always precomputed (one diagonal pixel ahead). It is
 * assumed that this diagonal pixel (x+1)(y+1) is set next. x and y
 * are adjusted by the step direction (sx, sy) if the diagonal pixel is the 
 * right candidate (via the two if statements).
 * @param p1 starting point p1(x1,y1)
 * @param p2 end point p2(x2,y2) 
 * @param img mlx_image
*/
void	plot_line(t_vector p1, t_vector p2, int color, t_img *mlx_img)
{
	t_bresenham	l;

	init_line(p1, p2, &l);
	while (l.x != (int)p2.x || l.y != (int)p2.y)
	{
		mlx_put_pixel_img(mlx_img, l.x, l.y, color);
		l.e2 = 2 * l.err;
		if (l.e2 >= l.dy)
		{
			l.err += l.dy;
			l.x += l.sx;
		}
		if (l.e2 <= l.dx)
		{
			l.err += l.dx;
			l.y += l.sy;
		}
	}
	mlx_put_pixel_img(mlx_img, l.x, l.y, color);
}

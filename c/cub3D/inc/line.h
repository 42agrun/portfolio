/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:20:49 by lbaumann          #+#    #+#             */
/*   Updated: 2023/08/29 15:10:10 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

/**
 * Struct to store necessary values for Bresenham algorithm
 * @param x x value of pixel that is drawn. initialized to start point
 * @param y x value of pixel that is drawn. initialized to start point
 * @param err error of diagonal pixel
 * @param e2 error of diagonal pixel precomputed
 * @param sx step in x direction. 1 if x2 > x1, else -1
 * @param sy step in y direction. 1 if y2 > y1, else -1
 * @param dy -abs(y2-y1) -> always negative
 * @param dx abs(x2-x1) -> always positive
*/
typedef struct s_bresenham
{
	int		x;
	int		y;
	int		err;
	int		e2;
	int		sx;
	int		sy;
	int		dy;
	int		dx;
	int		clr_step;
}t_bresenham;

void	plot_line(t_vector p1, t_vector p2, int color, t_img *mlx_img);

#endif

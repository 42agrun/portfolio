/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/07/05 10:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/*	Source to the mathematical formula which was used for this code: 
	https://stackoverflow.com/questions/2049582/
	how-to-determine-if-a-point-is-in-a-2d-triangle				*/

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	ax(a.getX());
	Fixed	ay(a.getY());
	Fixed	bx(b.getX());
	Fixed	by(b.getY());
	Fixed	cx(c.getX());
	Fixed	cy(c.getY());
	Fixed	px(point.getX());
	Fixed	py(point.getY());

	Fixed	ap_x = px - ax;
	Fixed	ap_y = py - ay;
	bool	p_ab = (bx - ax) * ap_y - (by - ay) * ap_x > 0;

	if (((cx - ax) * ap_y - (cy - ay) * ap_x > 0) == p_ab)
		return false;
	if (((cx - bx) * (py - by) - (cy - by) * (px - bx) > 0) != p_ab)
		return false;
	return true;
}

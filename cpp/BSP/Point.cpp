/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/07/05 10:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::~Point(void)
{
	return ;
}

Point::Point(const float _x, const float _y) : x(_x), y(_y)
{
	return ;
}

Point	&Point::operator=(Point &copy)
{
	return copy;
}

Point::Point(const Point &copy) : x(copy.getX()), y(copy.getY())
{
	return ;
}

Point::Point(void) : x(0), y(0)
{
	return ;
}

Fixed	Point::getX(void) const
{
	return this->x;
}

Fixed	Point::getY(void) const
{
	return this->y;
}
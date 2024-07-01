/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/07/05 10:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

void	fill_line(Point a, Point b, Point c, Point p)
{
	Fixed		ax(a.getX().toInt());
	Fixed		ay(a.getY().toInt());
	Fixed		bx(b.getX().toInt());
	Fixed		by(b.getY().toInt());
	Fixed		cx(c.getX().toInt());
	Fixed		cy(c.getY().toInt());
	Fixed		px(p.getX().toInt());
	Fixed		py(p.getY().toInt());
	Fixed		x = 1;
	static Fixed	y;
	static int	flag;

	if (flag != 42)
	{
		flag = 42;
		y = 10;
	}
	while (x < 11)
	{
		if (x == px && y == py)
			std::cout << " P  ";
		else if (x == ax && y == ay)
			std::cout << " A  ";
		else if (x == bx && y == by)
			std::cout << " B  ";
		else if (x == cx && y == cy)
			std::cout << " C  ";
		else
			std::cout << "    ";
		x = x + 1;
	}
	y = y - 1;
	std::cout << std::endl;
}

/*	For visualization purposes only a limited range will be supported.
	Numbers between 1 and 10 on the integer-scale can be displayed!		*/

void	draw_triangle(Point a, Point b, Point c, Point p)
{
	std::cout << std::endl;
	std::cout << "[10]", fill_line(a, b, c, p);
	std::cout << "[09]", fill_line(a, b, c, p);
	std::cout << "[08]", fill_line(a, b, c, p);
	std::cout << "[07]", fill_line(a, b, c, p);
	std::cout << "[06]", fill_line(a, b, c, p);
	std::cout << "[05]", fill_line(a, b, c, p);
	std::cout << "[04]", fill_line(a, b, c, p);
	std::cout << "[03]", fill_line(a, b, c, p);
	std::cout << "[02]", fill_line(a, b, c, p);
	std::cout << "[01]", fill_line(a, b, c, p);
	std::cout << "[XY][01][02][03][04][05][06][07][08][09][10]"; 
	std::cout << std::endl << std::endl;
}

int	main(void)
{
	Point	a( 5.0f, 3.0f );
	Point	b( 1.0f, 1.0f );
	Point	c( 1.0f, 5.0f );
	Point	p( 3.0f, 3.0f );

	draw_triangle(a, b, c, p);
	if (bsp(a, b, c, p))
		std::cout << "The point (P) is INSIDE of the triangle (ABC)." << std::endl;
	else
		std::cout << "The point (P) is OUTSIDE of the triangle (ABC)." << std::endl;
	return 0;
}

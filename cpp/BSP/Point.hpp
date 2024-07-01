/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:41:07 by agrun             #+#    #+#             */
/*   Updated: 2023/05/17 12:41:09 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include "Fixed.hpp"

class Point {
	private:
		Fixed const	x;
		Fixed const	y;
	public:
		Point(void);
		Point(const float _x, const float _y);
		Point(Point const &copy);
		~Point(void);

		Point		&operator=(Point &copy);
		Fixed		getX(void) const;
		Fixed		getY(void) const;
};

		bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif

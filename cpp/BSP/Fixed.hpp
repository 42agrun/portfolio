/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:41:07 by agrun             #+#    #+#             */
/*   Updated: 2023/05/17 12:41:09 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed {
	private:
		int			_value;
		static const int	_fractal;
	public:
		Fixed(void);
		Fixed(const int nbr);
		Fixed(const float nbr);
		Fixed(Fixed const &copy);
		~Fixed(void);
		int		getRawBits(void) const;
		void		setRawBits(int const raw);
		float		toFloat(void) const;
		int		toInt(void) const;

		Fixed		&operator=(Fixed const &copy);
		Fixed		operator+(Fixed const &copy) const;
		Fixed		operator-(Fixed const &copy) const;
		Fixed		operator*(Fixed const &copy) const;
		Fixed		operator/(Fixed const &copy) const;
		bool		operator==(Fixed const &copy) const;
		bool		operator!=(Fixed const &copy) const;
		bool		operator<=(Fixed const &copy) const;
		bool		operator>=(Fixed const &copy) const;
		bool		operator<(Fixed const &copy) const;
		bool		operator>(Fixed const &copy) const;

		Fixed	&operator++(void);
		Fixed	&operator--(void);
		Fixed	operator++(int nbr);
		Fixed	operator--(int nbr);
		
		static const Fixed	&min(Fixed const &copy1, Fixed const &copy2);
		static const Fixed	&max(Fixed const &copy1, Fixed const &copy2);
		static Fixed		&max(Fixed &copy1, Fixed &copy2);
		static Fixed		&min(Fixed &copy1, Fixed &copy2);
};

		std::ostream	&operator<<(std::ostream &str, Fixed const &fixed_nbr);

#endif

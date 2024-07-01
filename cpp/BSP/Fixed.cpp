/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <adrian@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/07/05 10:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_fractal = 8;

std::ostream	&operator<<(std::ostream &str, const Fixed &fixed_nbr)
{
	return (str << fixed_nbr.toFloat());
}

Fixed::~Fixed(void)
{
	return ;
}

int	Fixed::getRawBits(void) const
{
	return this->_value;
}

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

int	Fixed::toInt(void) const
{
	return this->_value >> this->_fractal;
}

float	Fixed::toFloat(void) const
{
	return (float)this->_value / (float)(1 << this->_fractal);
}

const Fixed	&Fixed::max(const Fixed &copy1, const Fixed &copy2)
{
	if (copy1.toFloat() > copy2.toFloat())
		return copy1;
	return copy2;
}

Fixed	&Fixed::max(Fixed &copy1, Fixed &copy2)
{
	if (copy1.toFloat() > copy2.toFloat())
		return copy1;
	return copy2;
}

const Fixed	&Fixed::min(const Fixed &copy1, const Fixed &copy2)
{
	if (copy1.toFloat() < copy2.toFloat())
		return copy1;
	return copy2;
}

Fixed	&Fixed::min(Fixed &copy1, Fixed &copy2)
{
	if (copy1.toFloat() < copy2.toFloat())
		return copy1;
	return copy2;
}

Fixed	Fixed::operator--(int nbr)
{
	Fixed	tmp = *this;

	(void)nbr;
	--this->_value;
	return tmp;
}

Fixed	Fixed::operator++(int nbr)
{
	Fixed	tmp = *this;

	(void)nbr;
	++this->_value;
	return tmp;
}

Fixed	&Fixed::operator--(void)
{
	this->_value--;
	return *this;
}

Fixed	&Fixed::operator++(void)
{
	this->_value++;
	return *this;
}

bool	Fixed::operator>(const Fixed &copy) const
{
	if (this->toFloat() > copy.toFloat())
		return true;
	return false;
}

bool	Fixed::operator<(const Fixed &copy) const
{
	if (this->toFloat() < copy.toFloat())
		return true;
	return false;
}

bool	Fixed::operator>=(const Fixed &copy) const
{
	if (this->toFloat() >= copy.toFloat())
		return true;
	return false;
}

bool	Fixed::operator<=(const Fixed &copy) const
{
	if (this->toFloat() <= copy.toFloat())
		return true;
	return false;
}

bool	Fixed::operator!=(const Fixed &copy) const
{
	if (this->toFloat() != copy.toFloat())
		return true;
	return false;
}

bool	Fixed::operator==(const Fixed &copy) const
{
	if (this->toFloat() == copy.toFloat())
		return true;
	return false;
}

Fixed	Fixed::operator/(const Fixed &copy) const
{
	return this->toFloat() / copy.toFloat();
}

Fixed	Fixed::operator*(const Fixed &copy) const
{
	return this->toFloat() * copy.toFloat();
}

Fixed	Fixed::operator-(const Fixed &copy) const
{
	return this->toFloat() - copy.toFloat();
}

Fixed	Fixed::operator+(const Fixed &copy) const
{
	return this->toFloat() + copy.toFloat();
}

Fixed	&Fixed::operator=(const Fixed &copy)
{
	this->_value = copy.getRawBits();
	return *this;
}

Fixed::Fixed(Fixed const &copy)
{
	*this = copy;
}

Fixed::Fixed(const float nbr)
{
	this->_value = roundf(nbr * (1 << this->_fractal));
}

Fixed::Fixed(const int nbr)
{
	this->_value = roundf(nbr * (1 << this->_fractal));
}

Fixed::Fixed(void)
{
	this->_value = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:51:57 by agrun             #+#    #+#             */
/*   Updated: 2022/12/06 09:52:02 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	ft_itoa.c: 1.	*/

static char	*str_conv(char *str, long nbr, long i)
{
	if (nbr == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		nbr = 147483648;
	}
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = nbr * -1;
	}
	while (nbr > 0)
	{
		str[i] = 48 + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	return (str);
}

/*	ft_itoa.c: 2.	*/

static int	len(long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		len++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (ft_return(len, 0));
}

/*	ft_itoa.c: 3.	*/

char	*ft_itoa(int n, char *str)
{
	long	nbr;
	long	i;

	nbr = n;
	i = len(nbr);
	if (n == 0)
	{
		str[0] = 48;
		str[1] = 0;
		return (str);
	}
	str[i] = 0;
	str[i--] = 0;
	str = str_conv(str, nbr, i);
	return (str);
}

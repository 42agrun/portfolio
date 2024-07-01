/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:37:28 by agrun             #+#    #+#             */
/*   Updated: 2023/04/25 12:37:35 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	ft_error_ex(int error)
{
	if (error == 1)
		write(2, "This map isn't rectangular!\n", 28);
	else if (error == 2)
		write(2, "This map is too small to function!\n", 35);
	else if (error == 3)
		write(2, "This map is missing border walls!\n", 34);
	else if (error == 4)
		write(2, "This map features duplicate exits or players!\n", 46);
	else if (error == 5)
		write(2, "This map is missing crucial game elements!\n", 43);
	else if (error == 6)
		write(2, "This map cannot be solved!\n", 27);
	else if (error == 7)
		write(2, "This map contains illegal characters!\n", 38);
	else if (error == 8)
	{
		write(2, "Sorry but the mapsize-limit has been reached!\n", 46);
		write(2, "The limit for this game is at 60 x 90 fields.\n", 46);
	}
	else if (error == 9)
		write(2, "Couldn't load MLX! Shutting down now.\n", 38);
	else if (error == 10)
		write(2, "Couldn't create a window! Shutting down now.\n", 45);
	else if (error == 11)
		write(2, "Couldn't create an image! Shutting down now.\n", 45);
}

/*	Custom-made error messages for pointing out various issues.		*/

int	ft_error(int error)
{
	write(2, "Error\n", 6);
	if (error == -1)
		write(2, "Number of arguments is not sufficient!\n", 39);
	else if (error == -2)
		write(2, "The given file isn't in the .ber format!\n", 41);
	else if (error == -3)
		write(2, "The mapfile doesn't exist or can't be opened!\n", 46);
	else if (error == -4)
		write(2, "Malloc failed, not enough memory!\n", 34);
	else if (error > 0)
		ft_error_ex(error);
	return (1);
}

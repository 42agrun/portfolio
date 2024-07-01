/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:37:28 by agrun             #+#    #+#             */
/*   Updated: 2023/08/11 12:37:35 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	fd_test(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (ft_error(-6));
	}
	else
		close(fd);
	return (0);
}

static void	ft_error_ex(int error)
{
	if (error == 1)
		write(2, "The map is missing border walls!\n", 33);
	else if (error == 2)
		write(2, "The mapfile is incorrectly formatted!\n", 38);
	else if (error == 3)
		write(2, "The given colorcode is not compatible!\n", 39);
	else if (error == 4)
		write(2, "The map contains illegal characters!\n", 37);
	else if (error == 5)
		write(2, "Couldn't load MLX! Shutting down now.\n", 38);
	else if (error == 6)
		write(2, "Couldn't create a window! Shutting down now.\n", 45);
	else if (error == 7)
		write(2, "Couldn't create an image! Shutting down now.\n", 45);
}

/*	Custom-made error messages for pointing out various issues.		*/

int	ft_error(int error)
{
	write(2, "Error\n", 6);
	if (error == -1)
		write(2, "Number of arguments is not sufficient!\n", 39);
	else if (error == -2)
		write(2, "The given file isn't in the .cub format!\n", 41);
	else if (error == -3)
		write(2, "The mapfile doesn't exist or can't be opened!\n", 46);
	else if (error == -4)
		write(2, "Malloc failed, not enough memory!\n", 34);
	else if (error == -5)
		write(2, "The size of the map exceeds the current support!\n", 49);
	else if (error == -6)
		write(2, "The texturefile doesn't exist or can't be opened!\n", 50);
	else if (error == -7 && BONUS == 1)
		write(2, "Incorrect usage of doors! Shutting down now.\n", 45);
	else if (error > 0)
		ft_error_ex(error);
	return (1);
}

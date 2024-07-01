/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:23:20 by agrun             #+#    #+#             */
/*   Updated: 2023/04/06 11:23:22 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	Wiping out the dimensional array once it's not needed anymore.		*/

int	ft_free_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	if (map)
	{
		free(map);
		map = NULL;
	}
	return (0);
}

/*	Had to split up the main function due to lack of available lines.
	The game and further setups occur from within the check_map function.	*/

static int	main_ex(char **map, int fd)
{
	if (read_file(fd, map))
	{
		ft_free_array(map);
		return (1);
	}
	close(fd);
	if (check_map(map))
	{
		ft_free_array(map);
		return (1);
	}
	return (0);
}

/*	Making sure the filename ends with ".ber", otherwise denying the file.
	Consider filepaths as part of the argument, look out for '/'!
	
	The filename needs to be 5 characters long at least, otherwise it's
	just a file that's named ".ber" instead of being that filetype!		*/

static int	check_fileformat(char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file[j])
	{
		if (file[j] == '/')
			i = 0;
		else
			i++;
		j++;
	}
	if (i < 5)
		return (1);
	j -= 4;
	if (file[j] == '.')
		if (file[j + 1] == 'b')
			if (file[j + 2] == 'e')
				if (file[j + 3] == 'r')
					return (0);
	return (1);
}

/*	Checking if a viable mapfile has been inserted before gamestart. 	*/

int	main(int argc, char **argv)
{
	char	**map;
	int		fd;

	if (argc != 2)
		return (ft_error(-1));
	if (check_fileformat(argv[1]))
		return (ft_error(-2));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (ft_error(-3));
	}
	map = malloc(sizeof(char *) * (60 + 1));
	if (!map)
	{
		close(fd);
		return (ft_error(-4));
	}
	if (main_ex(map, fd))
		return (1);
	return (0);
}

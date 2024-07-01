/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:23:20 by agrun             #+#    #+#             */
/*   Updated: 2023/09/05 17:10:46 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

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

int	clear_all_arrays(char **mapfile, char **map, char **data)
{
	if (mapfile)
		ft_free_array(mapfile);
	if (map)
		ft_free_array(map);
	if (data)
		ft_free_array(data);
	return (1);
}

/*	Used during parsing from map array into struct. Check extract_map_2.c!
	Separate function due to norminette/lack of available lines.		*/

int	check_map_information(char **map, int j, int i)
{
	if (BONUS == 1)
	{
		if (i > (int)ft_strlen(map[j])
			|| (map[j][i] != '0' && map[j][i] != '1'
			&& map[j][i] != '2' && map[j][i] != '3'))
			return (1);
	}
	else
	{
		if (i > (int)ft_strlen(map[j])
			|| (map[j][i] != '0' && map[j][i] != '1'))
			return (1);
	}
	return (0);
}

/*	Making sure the filename ends with ".cub", otherwise deny the file.
	Consider filepaths as part of the argument, look out for '/'!
	
	The filename needs to be 5 characters long at least, otherwise it's
	just a file that's named ".cub" instead of being that filetype!		*/

int	check_fileformat(char *file)
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
		if (file[j + 1] == 'c')
			if (file[j + 2] == 'u')
				if (file[j + 3] == 'b')
					return (0);
	return (1);
}

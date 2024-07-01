/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:26:02 by agrun             #+#    #+#             */
/*   Updated: 2023/09/06 10:55:19 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

static void	extract_xy(char **map, int x, int y, int *el)
{
	while (map[y])
	{
		while (map[y][x])
		{
			if (x > el[8])
				el[8] = x;
			x++;
		}
		x = 0;
		y++;
	}
	el[9] = y - 1;
}

static int	check_colorrange(int *colors)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (colors[i] > 255 || colors[i] < 0)
			return (ft_error(3));
		i++;
	}
	return (0);
}

static int	check_map_elements(int *el, char **map, char **data, int *xy)
{
	while (map[xy[1]])
	{
		xy[0] = skip_whitespaces(map[xy[1]], xy[0]);
		if (check_element(el, map, data, xy))
			return (1);
		xy[0]++;
		if (xy[0] >= (int)(ft_strlen(map[xy[1]])))
		{
			xy[0] = 0;
			xy[1]++;
		}
		if (el[0] && el[1] && el[2] && el[3] && el[4] && el[5] && !el[7])
			el[7] = xy[1];
	}
	if (!el[0] || !el[1] || !el[2] || !el[3] || !el[4] || !el[5] || !el[6])
		return (ft_error(2));
	return (0);
}

/*	The xy-integer array serves as a method to cut down on lines.
	It's used for going through the mapfile in other functions
	while checking for available elements.

	It's recommended to keep track of where exactly in the file
	the map is being shown, extract the line for that!

	elements[0] = 0;		// NO
	elements[1] = 0;		// SO
	elements[2] = 0;		// WE
	elements[3] = 0;		// EA
	elements[4] = 0;		// F
	elements[5] = 0;		// C
	elements[6] = 0;		// N/W/S/E (Player)
	elements[7] = 0;		// mapstart (rownumber)
	elements[8] = 0;		// max_x;
	elements[9] = 0;		// max_y;
	xy[0] = 0;			//x-value for map
	xy[1] = 0;			//y-value for map
	xy[2] = 0;			//substitute for "i"
	colors[0] = 0;			//R-value for F
	colors[1] = 0;			//G-value for F
	colors[2] = 0;			//B-value for F
	colors[3] = 0;			//R-value for C
	colors[4] = 0;			//G-value for C
	colors[5] = 0;			//B-value for C			*/

static void	set_elements(int *elements, int *xy, int *colors)
{
	elements[0] = 0;
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;
	elements[4] = 0;
	elements[5] = 0;
	elements[6] = 0;
	elements[7] = 0;
	elements[8] = 0;
	elements[9] = 0;
	xy[0] = 0;
	xy[1] = 0;
	xy[2] = 0;
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;
	colors[4] = 0;
	colors[5] = 0;
}

/*	The mapfile should contain information about the texture-filepaths
	as well as colorcodes for the floor- and ceilingtiles, these can be
	embedded in any desired order. 

	The map itself needs to be at the bottom of the file. Spaces are 
	supported, but make sure that the map is always closed off by walls!	

	Use an integer array to keep track of previously found elements.
	Make sure that the numbers for the colorcode do not exceed 255!		*/

int	check_map(t_setup *setup)
{
	set_elements(setup->elements, setup->xy, setup->colors);
	if (check_map_elements(setup->elements, setup->mapfile,
			setup->data, setup->xy))
		return (1);
	if (check_colors(setup->colors, setup->data, 0, 0))
		return (1);
	if (check_colorrange(setup->colors))
		return (1);
	if (extract_map(setup->mapfile, setup->map, 0, setup->elements[7]))
		return (1);
	extract_xy(setup->map, 0, 0, setup->elements);
	return (0);
}

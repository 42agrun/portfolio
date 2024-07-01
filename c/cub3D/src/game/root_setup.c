/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/08/14 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

static void	get_coord(t_root *root, t_setup *setup, int x, int y)
{
	if (y > setup->max_y || x > (int)ft_strlen(setup->map[y]))
		return ;
	if (setup->map[y][x] == 'N' || setup->map[y][x] == 'S'
		|| setup->map[y][x] == 'W' || setup->map[y][x] == 'E')
	{
		assign_vec(&root->game->pos, x, y);
		setup->map[y][x] = '0';
	}
}

/*	Transfering the content of the map to the root struct. The map struct 
	should only contain ones and zeroes, basically just floor and wall
	data since everything else will be held by the other struct classes!	

	Whitespaces on the map should be turned into walls to make the binary 
	mapdata readable.
	
	Look up main_utils.c for "check_map_information". 			*/

static int	map_parsing(t_root *root, t_setup *setup)
{
	int	i;
	int	j;

	j = 0;
	while (j < root->game->height + 1)
	{
		root->game->map[j] = malloc(sizeof(int) * (root->game->width + 1));
		if (root->game->map[j] == 0)
		{
			root_destroy(root, -1);
			return (ft_error(-4));
		}
		i = -1;
		while (++i < root->game->width + 1)
		{
			get_coord(root, setup, i, j);
			if (check_map_information(setup->map, j, i))
				root->game->map[j][i] = 1;
			else
				root->game->map[j][i] = setup->map[j][i] - '0';
		}
		j++;
	}
	return (0);
}

/*	Null-byte is being omitted for structs.					*/

static int	map_read(t_root *root, t_setup *setup)
{
	root->game->width = setup->elements[8];
	root->game->height = setup->elements[9];
	root->game->map = (int **)malloc(sizeof(int *) * (root->game->height + 1));
	if (root->game->map == 0)
	{
		root_destroy(root, -1);
		return (ft_error(-4));
	}
	if (map_parsing(root, setup))
		return (1);
	return (0);
}

/*	Creating struct classes for keeping track of map elements.

	el[6]	=>	N/W/S/E (Player)
	
	N =  0 /-1 	vector values	(78 ASCII)
	S =  0 / 1 	vector values	(83 ASCII)
	W = -1 / 0 	vector values	(87 ASCII)
	E =  1 / 0	vector values	(69 ASCII)

	el[8]	=>	max_x
	el[9] 	=>	max_y							*/

static int	game_init(t_root *root, t_setup *setup)
{
	root->game = ft_calloc(1, sizeof(t_game));
	if (root->game == 0)
		root_destroy(root, -1);
	if (root->game == 0)
		return (ft_error(-4));
	root->game->map = 0;
	root->game->dir.x = 0;
	root->game->dir.y = 0;
	if (setup->elements[6] == 78)
		root->game->dir.y = -1;
	else if (setup->elements[6] == 87)
		root->game->dir.x = -1;
	else if (setup->elements[6] == 83)
		root->game->dir.y = 1;
	else if (setup->elements[6] == 69)
		root->game->dir.x = 1;
	if (map_read(root, setup))
		return (1);
	return (0);
}

/*	Setting up the mandatory struct for MLX.				

	colors[0]	=>	R-value for F
	colors[1]	=>	G-value for F
	colors[2]	=>	B-value for F
	colors[3]	=>	R-value for C
	colors[4]	=>	G-value for C
	colors[5]	=>	B-value for C

	data[0]		=>	NO-texture-path
	data[1]		=>	SO-texture-path
	data[2]		=>	WE-texture-path
	data[3]		=>	EA-texture-path					*/

t_root	*root_setup(t_setup *setup)
{
	t_root			*root;

	root = ft_calloc(1, sizeof(t_root));
	if (!root)
	{
		root_destroy(root, -1);
		ft_error(-4);
		return (NULL);
	}
	root->game = 0;
	root->mlx = 0;
	root->mlx_win = 0;
	root->mlx_img = 0;
	root->rgb_f = mlx_rgb_to_int(0, setup->colors[0],
			setup->colors[1], setup->colors[2]);
	root->rgb_c = mlx_rgb_to_int(0, setup->colors[3],
			setup->colors[4], setup->colors[5]);
	if (game_init(root, setup) || renderer_init(root))
		return (NULL);
	if (texture_init(root, setup->data))
		return (clear_all_arrays(setup->mapfile, setup->map,
				setup->data), NULL);
	return (root);
}

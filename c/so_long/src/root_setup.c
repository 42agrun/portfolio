/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	get_coord(t_root *root, char **map, int *yx, int *obj)
{
	if (map[yx[0]][yx[1]] == 'P')
	{
		root->game->player.y = yx[0];
		root->game->player.x = yx[1];
		map[yx[0]][yx[1]] = '0';
	}
	else if (map[yx[0]][yx[1]] == 'E')
	{
		root->game->exit.y = yx[0];
		root->game->exit.x = yx[1];
		map[yx[0]][yx[1]] = '0';
	}
	else if (map[yx[0]][yx[1]] == 'C')
	{
		root->game->coll[*obj].y = yx[0];
		root->game->coll[*obj].x = yx[1];
		map[yx[0]][yx[1]] = '0';
		(*obj)++;
	}
}

/*	Transfering the content of the map onto the root struct. The map struct 
	should only contain ones and zeroes, basically just floor and wall
	data since everything else will be held by the other struct classes!	*/

static int	map_parsing(t_root *root, char **map)
{
	int	i;
	int	j;
	int	obj;
	int	yx[3];

	obj = 0;
	j = -1;
	while (++j < root->game->height)
	{
		root->game->map[j] = malloc(sizeof(int) * root->game->width);
		if (root->game->map[j] == 0)
		{
			root_destroy(root, -1);
			return (ft_error(-4));
		}
		i = -1;
		while (++i < root->game->width)
		{
			yx[0] = j;
			yx[1] = i;
			get_coord(root, map, yx, &obj);
			root->game->map[j][i] = (map[j][i] - 48);
		}
	}
	return (0);
}

/*	Null-byte is being omitted for structures.				*/

static int	map_read(t_root *root, char **map, int x, int y)
{
	root->game->width = x;
	root->game->height = y;
	root->game->coll
		= (t_coord *)malloc(sizeof(t_coord) * (root->game->count_coll));
	if (root->game->coll == 0)
	{
		root_destroy(root, -1);
		return (ft_error(-4));
	}
	root->game->map = (int **)malloc(sizeof(int *) * root->game->height);
	if (root->game->map == 0)
	{
		root_destroy(root, -1);
		return (ft_error(-4));
	}
	if (map_parsing(root, map))
		return (1);
	return (0);
}

/*	Creating struct classes for keeping track of map elements.		*/

static int	game_init(t_root *root, char **map, int x, int y)
{
	int	cep[4];

	check_map_elements(map, cep, 0, 0);
	root->game = (t_game *)malloc(sizeof(t_game));
	if (root->game == 0)
		root_destroy(root, -1);
	if (root->game == 0)
		return (ft_error(-4));
	root->game->map = 0;
	root->game->coll = 0;
	root->game->count_coll = cep[0];
	root->game->count_exit = cep[1];
	root->game->count_player = cep[2];
	root->game->player_move = 0;
	root->game->player_coll = 0;
	root->game->player_up = 0;
	root->game->player_down = 0;
	root->game->player_left = 0;
	root->game->player_right = 0;
	if (map_read(root, map, x, y))
		return (1);
	return (0);
}

/*	Setting up the mandatory struct for MLX.				*/

t_root	*root_setup(char **map, int x, int y)
{
	t_root			*root;

	root = (t_root *)malloc(sizeof(t_root));
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
	root->player = 0;
	root->exit = 0;
	root->coll = 0;
	root->wall = 0;
	root->ground = 0;
	if (game_init(root, map, x, y))
		return (NULL);
	if (renderer_init(root, 0))
		return (NULL);
	if (texture_init(root))
		return (NULL);
	return (root);
}

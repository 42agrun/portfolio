/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:03:40 by agrun             #+#    #+#             */
/*   Updated: 2023/04/21 11:04:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	game_destroy(t_game *game)
{
	int	i;

	if (game)
	{
		if (game->map)
		{
			i = 0;
			while (i < game->height + 1)
			{
				free(game->map[i]);
				i++;
			}
			free(game->map);
			game->map = NULL;
		}
		free(game);
		game = NULL;
	}
}

static void	wipe_mlx(t_root *root)
{
	root->wall_no = NULL;
	root->wall_so = NULL;
	root->wall_we = NULL;
	root->wall_ea = NULL;
	root->mlx_img = NULL;
	root->mlx_win = NULL;
	if (BONUS == 1)
	{
		root->door = NULL;
		root->door_open = NULL;
	}
	free(root->mlx);
	root->mlx = NULL;
	free(root);
	root = NULL;
}

static void	bonus_destroyer(t_root *root)
{
	if (root->minimap)
		mlx_destroy_image(root->mlx, root->minimap);
	if (BONUS == 0)
		return ;
	if (root->door)
		mlx_destroy_image(root->mlx, root->door);
	if (root->door_open)
		mlx_destroy_image(root->mlx, root->door_open);
}

void	root_destroy(t_root *root, int ex)
{
	if (root)
	{
		if (root->wall_no)
			mlx_destroy_image(root->mlx, root->wall_no);
		if (root->wall_so)
			mlx_destroy_image(root->mlx, root->wall_so);
		if (root->wall_we)
			mlx_destroy_image(root->mlx, root->wall_we);
		if (root->wall_ea)
			mlx_destroy_image(root->mlx, root->wall_ea);
		if (root->mlx_img)
			mlx_destroy_image(root->mlx, root->mlx_img);
		bonus_destroyer(root);
		if (root->mlx_win)
			mlx_destroy_window(root->mlx, root->mlx_win);
		if (root->mlx)
			mlx_destroy_display(root->mlx);
		if (root->game)
			game_destroy(root->game);
		wipe_mlx(root);
	}
	if (ex > -1)
		exit(ex);
}

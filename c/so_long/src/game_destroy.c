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

#include "../inc/so_long.h"

void	game_destroy(t_game *game)
{
	int	i;

	if (game)
	{
		if (game->coll)
			free(game->coll);
		if (game->map)
		{
			i = 0;
			while (i < game->height)
			{
				free(game->map[i]);
				game->map[i] = NULL;
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
	root->ground = NULL;
	root->wall = NULL;
	root->coll = NULL;
	root->exit = NULL;
	root->player = NULL;
	root->mlx_img = NULL;
	root->mlx_win = NULL;
	free(root->mlx);
	root->mlx = NULL;
	free(root);
	root = NULL;
}

void	root_destroy(t_root *root, int ex)
{
	if (root)
	{
		if (root->ground)
			mlx_destroy_image(root->mlx, root->ground);
		if (root->wall)
			mlx_destroy_image(root->mlx, root->wall);
		if (root->coll)
			mlx_destroy_image(root->mlx, root->coll);
		if (root->exit)
			mlx_destroy_image(root->mlx, root->exit);
		if (root->player)
			mlx_destroy_image(root->mlx, root->player);
		if (root->mlx_img)
			mlx_destroy_image(root->mlx, root->mlx_img);
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

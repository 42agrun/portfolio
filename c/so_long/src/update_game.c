/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:31:57 by agrun             #+#    #+#             */
/*   Updated: 2023/04/24 10:32:00 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	Counting the steps that have been taken.				*/

static void	has_moved(t_root *root, int x, int y)
{
	if (root->game->player.x != x || root->game->player.y != y)
	{
		root->game->player_move++;
		print_steps((int)root->game->player_move, root);
	}
}

/*	The coordinates of the picked up collectable get changed to negative
	values so that they cannot be reused again.				*/

static void	is_collectable(t_root *root)
{
	int				k;

	k = 0;
	while (k < root->game->count_coll)
	{
		if (root->game->coll[k].x == root->game->player.x
			&& root->game->coll[k].y == root->game->player.y)
		{
			root->game->coll[k].x = -1;
			root->game->coll[k].y = -1;
			root->game->player_coll++;
		}
		k++;
	}
}

/*	After taking a step the game will check the input and player position.	*/

void	update_game(t_root *root)
{
	int				x;
	int				y;

	x = root->game->player.x;
	y = root->game->player.y;
	if (root->game->player_up != 0)
		move_up(root, x, y);
	else if (root->game->player_down != 0)
		move_down(root, x, y);
	else if (root->game->player_left != 0)
		move_left(root, x, y);
	else if (root->game->player_right != 0)
		move_right(root, x, y);
	has_moved(root, x, y);
	is_collectable(root);
	draw(root);
	if (root->game->exit.x == root->game->player.x
		&& root->game->exit.y == root->game->player.y)
		if (root->game->count_coll == root->game->player_coll)
			root_destroy(root, 0);
}

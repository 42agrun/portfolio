/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:47:51 by agrun             #+#    #+#             */
/*   Updated: 2023/04/21 12:47:57 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	The very first condition checks for the ESC-key to close the game with.	*/

int	key_press(int keycode, t_root *root)
{
	if (keycode == 65307)
		root_destroy(root, 0);
	if (keycode == 119)
		root->game->player_up = 1;
	if (keycode == 115)
		root->game->player_down = 1;
	if (keycode == 97)
		root->game->player_left = 1;
	if (keycode == 100)
		root->game->player_right = 1;
	update_game(root);
	return (0);
}

/*	Returning to the initial values after the keypress has been processed.	*/

int	key_release(int keycode, t_root *root)
{
	if (keycode == 119)
		root->game->player_up = 0;
	if (keycode == 115)
		root->game->player_down = 0;
	if (keycode == 97)
		root->game->player_left = 0;
	if (keycode == 100)
		root->game->player_right = 0;
	update_game(root);
	return (0);
}

/*	This function is being used to close the window via the mouse.		*/

int	destroy_hook(int keycode, t_root *root)
{
	(void)keycode;
	(void)root;
	root_destroy(0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/08/14 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../inc/line.h"
#include "../libft/includes/libft.h"

int	game_loop(t_root *root)
{
	iterate_width(root, root->game);
	generate_minimap(root->minimap, root->game);
	display_minimap(root, root->game);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
	mouse_move(0, 0, 0, root);
	return (0);
}

/*	This function is being used to close the window via the mouse.	*/
int	destroy_hook(int keycode, t_root *root)
{
	(void)keycode;
	(void)root;
	root_destroy(0, 0);
	return (0);
}

/**
 * Used for setting up the game and only during that instance.
 * 
 * Clearing out the dimensional array from the main since we will not 
 * return to that function anymore due to the ensuing permanent loop.
 * 
 * destroy_hook -> called when esc is pressed
 * key_press -> called when any key is pressed
 * mouse_move -> called when mouse movement is detected
 * game->loop -> called by mlx inside the mlx_loop, renders
 * new image frame
 * 
*/
int	game_setup(t_root *root, t_setup *setup)
{
	t_vector	plane;

	root->game->pos.x += MIN_WALL_DIST;
	root->game->pos.y += MIN_WALL_DIST;
	clear_all_arrays(setup->map, setup->mapfile, setup->data);
	plane = rotate_vec(root->game->dir, M_PI / 2);
	assign_vec(&root->game->plane, plane.x * FOV, plane.y * FOV);
	root->minimap = mlx_new_image(root->mlx,
			(root->game->width + 1) * MINIMAP_TILE_SZ,
			(root->game->height + 1) * MINIMAP_TILE_SZ);
	mlx_hook(root->mlx_win, 17, 1L << 17, destroy_hook, root);
	mlx_hook(root->mlx_win, 2, 1L << 0, key_press, root);
	mlx_mouse_hook(root->mlx_win, &mouse_move, root);
	mlx_loop_hook(root->mlx, game_loop, root);
	mlx_loop(root->mlx);
	return (0);
}

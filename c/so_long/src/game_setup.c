/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

/*	The ex multiplier makes sure to let the pixel grabber know if the
	sprites have to be scaled down accordingly. 64 x 64 is base.		*/

static void	draw_square(t_root *root, t_img *img, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;
	int				px;
	int				ex;

	px = determine_pixelsize(root);
	ex = 1;
	if (px == 32)
		ex = 2;
	if (px == 16)
		ex = 4;
	j = 0;
	while (j * ex < 64)
	{
		i = 0;
		while (i * ex < 64)
		{
			color = mlx_get_pixel(img, i * ex, j * ex);
			if (color != mlx_rgb_to_int(0, 255, 255, 255))
				mlx_draw_pixel(root->mlx_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_env(t_root *root, int i, int j, int px)
{
	int	k;

	if (root->game->exit.x == i && root->game->exit.y == j)
		draw_square(root, root->exit, i * px, j * px);
	k = -1;
	while (++k < root->game->count_coll)
		if (root->game->coll[k].x == i && root->game->coll[k].y == j)
			draw_square(root, root->coll, i * px, j * px);
	if (root->game->player.x == i && root->game->player.y == j)
		draw_square(root, root->player, i * px, j * px);
}

static void	draw_map(t_root *root, int px)
{
	int	i;
	int	j;

	px = determine_pixelsize(root);
	j = 0;
	while (j < root->game->height)
	{
		i = 0;
		while (i < root->game->width)
		{
			if (root->game->map[j][i] == 1)
				draw_square(root, root->wall, i * px, j * px);
			else
				draw_square(root, root->ground, i * px, j * px);
			draw_env(root, i, j, px);
			i++;
		}
		j++;
	}
}

/*	This abridged function gets used to update the map after moving.	*/

void	draw(t_root *root)
{
	draw_map(root, 0);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
}

/*	Used for setting up the game and only during that instance.

	Clearing out the dimensional array from the main since we will not 
	return to that function anymore due to the ensuing permanent loop.	*/

int	game_setup(t_root *root, char **map)
{
	ft_free_array(map);
	draw_map(root, 0);
	mlx_put_image_to_window(root->mlx, root->mlx_win, root->mlx_img, 0, 0);
	mlx_hook(root->mlx_win, 2, 1L << 0, key_press, root);
	mlx_hook(root->mlx_win, 3, 1L << 1, key_release, root);
	mlx_hook(root->mlx_win, 17, 1L << 17, destroy_hook, root);
	mlx_loop(root->mlx);
	return (0);
}

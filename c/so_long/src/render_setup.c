/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/04/05 10:29:17 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	determine_pixelsize(t_root *root)
{
	if (root->game->height > 30 || root->game->width > 60)
		return (16);
	else if (root->game->height > 15 || root->game->width > 30)
		return (32);
	else
		return (64);
}

static int	texture_load(t_root *root, t_img **img, char *path)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(root->mlx, path, &width, &height);
	if (*img == 0)
	{
		root_destroy(root, -1);
		write(2, "Error\n", 6);
		write(2, "Failed to load texture(s)! Shutting down now.\n", 46);
		return (1);
	}
	(*img)->width = width;
	(*img)->height = height;
	return (0);
}

int	texture_init(t_root *root)
{
	if (texture_load(root, &root->player, "./xpm/player_a.xpm"))
		return (1);
	if (texture_load(root, &root->exit, "./xpm/exit.xpm"))
		return (1);
	if (texture_load(root, &root->coll, "./xpm/carrot.xpm"))
		return (1);
	if (texture_load(root, &root->wall, "./xpm/wall.xpm"))
		return (1);
	if (texture_load(root, &root->ground, "./xpm/floor.xpm"))
		return (1);
	return (0);
}

int	renderer_init(t_root *root, int px)
{
	px = determine_pixelsize(root);
	root->mlx = mlx_init();
	if (root->mlx == 0)
	{
		root_destroy(root, -1);
		return (ft_error(9));
	}
	root->mlx_win = mlx_new_window(root->mlx, root->game->width * px,
			root->game->height * px, "so_long");
	if (root->mlx_win == 0)
	{
		root_destroy(root, -1);
		return (ft_error(10));
	}
	root->mlx_img = mlx_new_image(root->mlx, root->game->width * px,
			root->game->height * px);
	if (root->mlx_img == 0)
	{
		root_destroy(root, -1);
		return (ft_error(11));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:29:14 by agrun             #+#    #+#             */
/*   Updated: 2023/08/30 12:03:32 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	texture_load(t_root *root, t_img **img, char *path)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(root->mlx, path, &width, &height);
	if (*img == 0)
	{
		write(2, "Error\n", 6);
		write(2, "Failed to load texture(s)! Shutting down now.\n", 46);
		root_destroy(root, -1);
		return (1);
	}
	(*img)->width = width;
	(*img)->height = height;
	return (0);
}

/*	data[0]		=>	NO-texture-path
	data[1]		=>	SO-texture-path
	data[2]		=>	WE-texture-path
	data[3]		=>	EA-texture-path					*/

int	texture_init(t_root *root, char **data)
{
	int	i;

	i = -1;
	while (++i && i < 4 && fd_test(data[i]))
		return (1);
	if (texture_load(root, &root->wall_no, data[0]))
		return (1);
	if (texture_load(root, &root->wall_so, data[1]))
		return (1);
	if (texture_load(root, &root->wall_we, data[2]))
		return (1);
	if (texture_load(root, &root->wall_ea, data[3]))
		return (1);
	if (BONUS == 1)
		if ((texture_load(root, &root->door, "./xpm/door.xpm"))
			|| (texture_load(root, &root->door_open, "./xpm/door_open.xpm")))
			return (1);
	root->mlx_win = mlx_new_window(root->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (root->mlx_win == 0)
	{
		root_destroy(root, -1);
		return (ft_error(6));
	}
	return (0);
}

int	renderer_init(t_root *root)
{
	root->mlx = mlx_init();
	if (root->mlx == 0)
	{
		root_destroy(root, -1);
		return (ft_error(5));
	}
	root->mlx_img = mlx_new_image(root->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (root->mlx_img == 0)
	{
		root_destroy(root, -1);
		return (ft_error(7));
	}
	return (0);
}

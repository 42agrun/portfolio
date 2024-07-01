/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:47:51 by agrun             #+#    #+#             */
/*   Updated: 2023/09/04 15:26:44 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"
#include "../../libft/includes/libft.h"
#include "../../inc/math_framework.h"

static int	mouse_move_bonus(int x, int y, t_root *root)
{
	static int	new_flag;
	static int	old_xx;
	static int	old_yy;

	if (new_flag != 42)
	{
		mlx_mouse_get_pos(root->mlx, root->mlx_win, &x, &y);
		old_xx = x;
		old_yy = y;
		new_flag = 42;
	}
	mlx_mouse_get_pos(root->mlx, root->mlx_win, &x, &y);
	if (x > old_xx + 4)
	{
		mlx_mouse_move(root->mlx, root->mlx_win, old_xx, old_yy);
		rotate_right(root->game);
	}
	else if (x < old_xx - 4)
	{
		mlx_mouse_move(root->mlx, root->mlx_win, old_xx, old_yy);
		rotate_left(root->game);
	}
	return (0);
}

int	mouse_move(int mousecode, int x, int y, t_root *root)
{
	static int	flag;
	static int	old_x;

	(void)mousecode;
	if (BONUS == 1)
		return (mouse_move_bonus(x, y, root));
	if (flag != 42)
	{
		mlx_mouse_get_pos(root->mlx, root->mlx_win, &x, &y);
		old_x = x;
		flag = 42;
	}
	mlx_mouse_get_pos(root->mlx, root->mlx_win, &x, &y);
	if (x > old_x + 4)
	{
		rotate_right(root->game);
	}
	else if (x < old_x - 4)
	{
		rotate_left(root->game);
	}
	old_x = x;
	return (0);
}

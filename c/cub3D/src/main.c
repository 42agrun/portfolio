/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:23:20 by agrun             #+#    #+#             */
/*   Updated: 2023/09/06 15:32:49 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

t_root	*parse(char *map_name, t_setup *setup)
{
	int			fd;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_error(-3), NULL);
	setup->max_y = n_lines(fd);
	if (close(fd) == -1 || setup->max_y == 1)
		return (NULL);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_error(-3), NULL);
	setup->map = ft_calloc((setup->max_y + 1), sizeof(char *));
	setup->mapfile = ft_calloc((setup->max_y + 1), sizeof(char *));
	setup->data = ft_calloc((6 + 1), sizeof(char *));
	if (!setup->map || !setup->mapfile || !setup->data)
		return (ft_error(-4), NULL);
	if (read_file(fd, setup->mapfile, 0, setup->max_y))
		return (clear_all_arrays(setup->mapfile,
				setup->map, setup->data), NULL);
	if (close(fd) == -1)
		return (NULL);
	if (check_map(setup) == 1)
		return (clear_all_arrays(setup->mapfile,
				setup->map, setup->data), NULL);
	return (root_setup(setup));
}

int	main(int argc, char **argv)
{
	t_root	*root;
	t_setup	setup;

	if (argc != 2)
		return (ft_error(-1));
	if (check_fileformat(argv[1]))
		return (ft_error(-2));
	root = parse(argv[1], &setup);
	if (!root)
		return (EXIT_FAILURE);
	if (game_setup(root, &setup))
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

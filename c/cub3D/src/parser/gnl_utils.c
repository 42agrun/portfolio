/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:58:10 by agrun             #+#    #+#             */
/*   Updated: 2023/09/06 11:03:36 by lbaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../libft/includes/libft.h"

static int	n_loop(int fd, char *buff, ssize_t rd_bytes, int i)
{
	buff[0] = 0;
	buff[1] = 0;
	rd_bytes = -1;
	while (!ft_strchr(buff, 10) && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, 1);
		if (rd_bytes == 0 || !buff[0])
			return (-1);
		else if (buff[0] == '\n')
			return (++i);
		buff[0] = 0;
		buff[1] = 0;
	}
	return (-1);
}

/*	This function is used to determine how large the mapfile is so that we
	may malloc the exact number of required lines in the dimensional array.	*/

int	n_lines(int fd)
{
	char	*buff;
	ssize_t	rd_bytes;
	int		i;
	int		r;

	buff = malloc(sizeof(char) * (2));
	if (!buff)
		return (ft_error(-4));
	i = 0;
	r = 1;
	rd_bytes = -1;
	while (r > 0)
	{
		r = n_loop(fd, buff, rd_bytes, i);
		if (r > 0)
			i = r;
	}
	i++;
	ft_free(&buff);
	return (i);
}

static char	*bad_read(char **buff, int *fd_flag)
{
	ft_free(&*buff);
	fd_flag[0] = 42;
	return (NULL);
}

static char	*read_map(int fd, int *fd_flag, char *map)
{
	char	*buff;
	ssize_t	rd_bytes;
	int		flag;

	buff = ft_calloc(2, sizeof(char));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	rd_bytes = -1;
	flag = 0;
	while (!ft_strchr(buff, 10) && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, 1);
		if (rd_bytes == 0 || !buff[0])
			return (ft_free(&buff), fd_flag[0] = 0, map);
		buff[rd_bytes] = 0;
		map = ft_str_join(map, buff, flag);
		flag++;
		if (!map)
			return (bad_read(&buff, fd_flag));
	}
	ft_free(&buff);
	return (map);
}

/*	Function for reading and checking the file within the filedescriptor.
	Converting the contents into a dimensional array for later conversion.
	
	Overwriting n-bytes with null-bytes after extracting the content.	*/

int	read_file(int fd, char **map, int y, int max_y)
{
	int		fd_flag[2];
	int		x;

	fd_flag[0] = 1;
	fd_flag[1] = 0;
	while (fd_flag[0])
	{
		if (y == max_y + 1)
			return (ft_error(-5));
		map[y] = read_map(fd, fd_flag, map[y]);
		if (fd_flag[0] == 42)
			return (ft_error(-4));
		else if (!fd_flag[0])
			y--;
		x = (int)ft_strlen(map[y]) - 1;
		if (x >= 0 && map[y][x] < 32)
			map[y][x] = 0;
		y++;
	}
	if (!map[y])
		y--;
	map[y][ft_strlen(map[y])] = 0;
	map[y + 1] = 0;
	return (0);
}

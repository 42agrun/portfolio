/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:58:10 by agrun             #+#    #+#             */
/*   Updated: 2023/04/06 11:58:13 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

static char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != 0)
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

static char	*read_map(int fd, int *fd_flag, char *map)
{
	char	*buff;
	ssize_t	rd_bytes;

	buff = malloc(sizeof(char) * (2));
	if (!buff)
		return (NULL);
	rd_bytes = -1;
	while (!ft_strchr(buff, 10) && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, 1);
		if (rd_bytes == 0 || !buff[0])
		{
			ft_free(&buff);
			fd_flag[0] = 0;
			return (map);
		}
		buff[rd_bytes] = 0;
		map = ft_strjoin(map, buff);
		if (!map)
			ft_free(&buff);
		if (!map)
			return (NULL);
	}
	ft_free(&buff);
	return (map);
}

/*	Function for reading and checking the file within the filedescriptor.
	Converting the contents into a dimensional array for later conversion.
	
	Ovrwriting n-bytes with null-bytes after extracting the content.	*/

int	read_file(int fd, char **map)
{
	int		y;
	int		fd_flag[2];
	char	temp;

	y = 0;
	fd_flag[0] = 1;
	fd_flag[1] = 0;
	while (fd_flag[0])
	{
		if (y == 61)
			return (ft_error(8));
		map[y] = read_map(fd, fd_flag, map[y]);
		if (!map[y] && fd_flag[0])
			return (ft_error(-4));
		else if (!map[y] && !fd_flag[0])
			y--;
		temp = map[y][ft_strlen(map[y]) - 1];
		map[y][ft_strlen(map[y]) - 1] = 0;
		y++;
	}
	map[y - 1][ft_strlen(map[y - 1])] = temp;
	map[y] = 0;
	return (0);
}

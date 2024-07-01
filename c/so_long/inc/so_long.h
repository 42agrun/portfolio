/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:32:59 by agrun             #+#    #+#             */
/*   Updated: 2023/03/18 10:33:02 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*	Mandatory libraries for read, malloc and fd related commands.		*/

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/*	Headerfiles from the MLX library, referring to X11 inside.		*/

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

/*	Structs for keeping track of map/game information. Necessary for MLX!	*/

typedef struct s_coord
{
	int				x;
	int				y;
}				t_coord;

typedef struct s_game
{
	int				**map;
	int				height;
	int				width;
	t_coord			player;
	int				player_up;
	int				player_down;
	int				player_left;
	int				player_right;
	int				player_move;
	int				player_coll;
	t_coord			exit;
	t_coord			*coll;
	int				count_coll;
	int				count_exit;
	int				count_player;
}				t_game;

typedef struct s_root
{
	void			*mlx;
	void			*mlx_win;
	t_img			*mlx_img;
	t_game			*game;
	t_img			*player;
	t_img			*exit;
	t_img			*coll;
	t_img			*wall;
	t_img			*ground;
}				t_root;

/*	Taken from libft. Used for converting during GNL and step printout.	*/

char			*ft_strjoin(char *archive, char *buff);
char			*ft_itoa(int n);

/*	Functions for setting up the game itself.				*/

t_root			*root_setup(char **map, int x, int y);
void			find_player_pos(char **map, int *pp);
int				check_map(char **map);
int				check_map_elements(char **map, int *cep, int x, int y);
int				check_map_path(char **map, int *cep, int x_size, int y_size);
int				read_file(int fd, char **map);
int				flood_map(char **map, int *pp, int *cep);
int				renderer_init(t_root *root, int px);
int				texture_init(t_root *root);
int				game_setup(t_root *root, char **map);

/*	MLX support functions.							*/

void			mlx_draw_pixel(t_img *mlx_img, int x, int y, int color);
unsigned int	mlx_get_pixel(t_img *img, int x, int y);
unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);

/*	Functions for controlling the game.					*/

void			move_right(t_root *root, int x, int y);
void			move_left(t_root *root, int x, int y);
void			move_up(t_root *root, int x, int y);
void			move_down(t_root *root, int x, int y);
void			update_game(t_root *root);
void			print_steps(int steps, t_root *root);
void			draw(t_root *root);
int				determine_pixelsize(t_root *root);
int				key_press(int keycode, t_root *root);
int				key_release(int keycode, t_root *root);
int				destroy_hook(int keycode, t_root *root);

/*	Functions for shutting down and clearing out leftover content.		*/

void			root_destroy(t_root *root, int ex);
void			game_destroy(t_game *game);
void			ft_free(char **str);
int				ft_free_array(char **map);
int				ft_error(int error);

#endif

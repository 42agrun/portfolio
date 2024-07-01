/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:32:59 by agrun             #+#    #+#             */
/*   Updated: 2023/08/10 10:33:02 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*	Mandatory libraries for read, malloc and fd related commands.		*/

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

/*	Headerfiles from the MLX library, referring to X11 inside.		*/

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

/*	local Header files 	*/
# include "math_framework.h"
# include "minimap.h"
# include "line.h"

# ifndef BONUS
#  define BONUS 0
# endif

/*  	Macros			*/

# define WIN_HEIGHT 512
# define WIN_WIDTH 1024

# define BLUE 0xFF0000FF
# define LIGHT_BLUE 0xFF1595EB
# define GREEN 0xFF00FF00
# define RED 0xFFFF0000
# define PURPLE 0xFF813BB8
# define YELLOW 0xFFE7EB15
# define WHITE 0xFFFFFFFF
# define BROWN 0xFF4A3310
# define BLACK 0

# define PLAYER_SPEED_MOV 0.1
# define PLAYER_SPEED_ROT 0.04
# define MIN_WALL_DIST 0.2

/*	MLX keys		*/
# define MLX_ESC 65307
# define MLX_W 119
# define MLX_S 115
# define MLX_A 97
# define MLX_D 100
# define MLX_E 101
# define MLX_ARROW_L 65361
# define MLX_ARROW_R 65363

# define FOV 0.66

/*	Structs for keeping track of map/game information. Necessary for MLX!	*/

/**
 * @param map 2D-map array that stores the parsed map
 * @param map_pos position in map array (used to index map array) and
 * 					check for hit
 * @param step will be added to map_pos. assigned based on ray_dir
 * @param pos exact position of player
 * @param dir direction that player is looking (normalized to 1)
 * 				-> rotated with arrow keys/mouse movement
 * 				-> 0/-1 = north | 0/1 = south | -1/0 = west | 1/0 = east
 * @param plane perpendicular to direction vector (FOV is determined by
 * 					 the ratio of the length of plane to dir vector)
 * @param ray_dir vector describing an individual ray
 * @param delta_grid dist between horizontal/vertical gridlines
 * @param side_dist dist to nearest hor/ver gridline from pos
 * @param ortho_wall_dist distance of orthogonal vector to camer plane to wall
 * @param hit true: wall was hit
 * @param side true: horizontal wall hit
 * @param width width of the map - 1
 * @param height height of the map - 1
 * @param minimap_rays store ray_dir vectors for the minimap display later
 * @param minimap_rays_dist store each rays ortho_wall_dist for minimap
*/
typedef struct s_game
{
	int				**map;
	t_vec_int		map_pos;
	t_vec_int		step;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		ray_dir;
	t_vector		delta_grid;
	t_vector		side_dist;
	float			ortho_wall_dist;
	bool			hit;
	bool			side;
	int				width;
	int				height;
	t_vector		minimap_rays[WIN_WIDTH];
	float			minimap_rays_dist[WIN_WIDTH];
}				t_game;

/*	Four different textures for displaying walls to meet the requirements
	from the project description. The mapfile will contain the filepaths
	to the various textures.

	There are no textures for floor or ceiling, instead predetermined
	colors will be displayed. Information about the colors of the floor 
	and ceiling is stored within the respective rgb-attribute arrays.	*/
typedef struct s_root
{
	void			*mlx;
	void			*mlx_win;
	t_img			*mlx_img;
	t_game			*game;
	t_img			*minimap;
	t_img			*wall_no;
	t_img			*wall_so;
	t_img			*wall_we;
	t_img			*wall_ea;
	t_img			*door;
	t_img			*door_open;
	int				rgb_f;
	int				rgb_c;
}				t_root;

typedef struct s_setup
{
	int			max_y;
	char		**data;
	int			elements[10];
	int			xy[3];
	int			colors[6];
	char		**mapfile;
	char		**map;
}				t_setup;

/*	Taken from libft. Used for converting during GNL.			*/
char			*ft_str_join(char *archive, char *buff, int flag);

/*	Functions for setting up the game itself.				*/
t_root			*root_setup(t_setup *setup);
int				check_map(t_setup *setup);
int				check_element(int *el, char **map, char **data, int *xy);
int				check_element_ex(int *el, char **map, char **data, int *xy);
int				check_colors(int *colors, char **data, int i, int j);
int				extract_map(char **mapfile, char **map, int x, int yy);
int				check_map_edge(char *map, int x, int xx);
int				check_walls(char **map, int x, int y, int max_x);
int				check_map_information(char **map, int j, int i);
int				skip_commas(char *str, int i);
int				is_a_space(char *str, int i);
int				skip_whitespaces(char *str, int i);
int				illegal_character(char *str, int i);
int				ft_array_size(char **str);
int				n_lines(int fd);
int				check_fileformat(char *file);
int				read_file(int fd, char **map, int y, int max_y);
int				renderer_init(t_root *root);
int				texture_init(t_root *root, char **data);
int				game_setup(t_root *root, t_setup *setup);

/*	MLX support functions.							*/
unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);
void			mlx_put_pixel_img(t_img *mlx_img, int x, int y, int color);
void			mlx_int_to_rgb(int color, int *r, int *g, int *b);

/*	Functions for controlling the game.					*/
int				key_press(int keycode, t_root *root);
void			rotate_right(t_game *game);
void			rotate_left(t_game *game);
bool			no_collision(t_game *game, t_vector new_pos);
bool			check_door(t_game *game);

/* Player movement*/
void			move_fwd(t_game *game);
void			move_bwd(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);

/*	Mouse movement		*/
int				mouse_move(int mousecode, int x, int y, t_root *root);

/*	Functions for shutting down and clearing out leftover content.		*/
void			root_destroy(t_root *root, int ex);
void			game_destroy(t_game *game);
void			ft_free(char **str);
int				clear_all_arrays(char **mapfile, char **map, char **data);
int				ft_free_array(char **map);
int				ft_error(int error);
int				fd_test(char *file);

/*	Minimap			*/
void			display_minimap(t_root *root, t_game *game);
void			generate_minimap(t_img *minimap, t_game *game);

/*	Raycast			*/
void			iterate_width(t_root *root, t_game *game);
#endif

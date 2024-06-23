/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 08:55:05 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 14:06:30 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# ifdef __APPLE__				
#  define WIDTH 2400
#  define HEIGHT 1350
# elif defined(__linux__)	
#  define WIDTH 1500
#  define HEIGHT 850
# endif

typedef	enum e_tile
{
	EMPTY,
	WALL,
	FLOOR,
	PLAYER_N,
	PLAYER_E,
	PLAYER_S,
	PLAYER_W,
	TEMP,
}	t_tile;

typedef enum e_token
{
	NO,
	SO,
	WE,
	EA,
	FLOOR_COLOR,
	CEILING_COLOR,
	UNKNOWN,
}	t_token;

typedef struct s_draw
{
	double	wall_x;
	int		text_x;
	int		text_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
} t_draw;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct s_assets
{
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	t_textures	textures;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
}	t_assets;

typedef struct s_map
{
	char	**map;
	t_tile	**grid;
	int		player_x;
	int		player_y;
	int		width;
	int 	height;
	t_assets	assets;
} t_map;


typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_ray
{
	t_vect	hit_spot;
	double	ray_dir_x;
	double	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_ray_data
{
	t_vect	ray_dir;
	t_vect	start_pos;
	t_vect	hit_spot;
	int		side;
	float	perp_wall_dist;
}	t_ray_data;

typedef struct s_player
{
	float	move_speed;
	float	rotation_speed;
	int		turn_direction;
	t_vect	direction;
	t_vect	position;
	t_vect	plane;
}	t_player;

typedef struct s_main
{
	mlx_t		*window;
	mlx_image_t	*image;
	t_player	player;
	t_map		map;
	float		fov;
	float		render_distance;
	double      previous_mouse_x;
	double      previous_mouse_y;
	int			mouse;
}	t_main;

typedef bool (*t_action)(t_assets *, char *);


bool		end_program(t_main *main);

// PARSING FUNCTIONS
bool		parser(char *file, t_main *main); //
bool		map_ext_check(char *path); //
bool		check_order(char **map_line); //
bool		open_file(char *path, int *fd); //
bool		check_map(t_main *main); //
bool		parse_assets(t_assets *assets, char **line); //
bool		read_file(int file, t_map *map); //
bool		init_map(t_main *main); // 
void		set_tiles(t_map *map); //

// MAP FUNCTIONS
bool		check_map_char(char c); //
bool		check_map_str(char *str); //
int			find_map_start(char **map); //
bool		find_map_height(t_map *map); //
bool		find_map_width(t_map *map); //
uint32_t	parse_color(int r, int g, int b, int n); //

// PARSER UTILS
bool		parse_no(t_assets *assets, char *path); //
bool		parse_so(t_assets *assets, char *path); //
bool		parse_we(t_assets *assets, char *path); //
bool		parse_ea(t_assets *assets, char *path); //
bool		parse_floor(t_assets *assets, char *color); //
bool		parse_ceiling(t_assets *assets, char *color); //

// RENDERING FUNCTIONS
void		draw_wall(uint32_t x, t_ray_data ray, t_main *main, mlx_texture_t *text);
mlx_texture_t	*get_texture(t_ray_data *ray, t_textures *textures);//
void		draw_F_C(t_main *main);//
void		render_single_frame(t_main *main);//
t_ray_data	cast_ray(t_vect position, t_vect direction, t_map map);//
void		set_distance(t_ray *ray);//
void		set_hit_spot(t_ray *ray, t_vect position, t_vect direction);//

// GAME FUNCTIONS
void		init_ray(t_ray *ray, t_vect position, t_vect direction);//
bool		init_game(t_main *main);//
bool		game_loop(t_main *main);//
void		game_controls(t_main *main);//
t_vect		rotate_vector(t_vect vector, float angle);//
t_vect		move_vector(t_main *main);//
void		hit_check(t_main *main, t_vect position, t_vect move);//
void 		mouse_update(double xdelta, double ydelta, void *param);//
void		key_hook(mlx_key_data_t keydata, void *param);//
bool	    end_program(t_main *main);

//RANDOM UTILS
char	**matrix_add(char *arr[], char *str);
int		matrix_len(char **p_arr);
void	matrix_free(char **p_arr);
void	error_msg(const char *message, t_main *main);
t_vect	normalize_vector(t_vect vector);
void    clear(t_main *main);






#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:44:34 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/01 20:09:55 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/include/libft.h"
# include <MLX42.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT 900

typedef enum e_token_pars
{
	EMPTY_LINE,
	MAP,
	INFO,
	ERROR,
}	t_token_pars;

typedef enum e_action_pars
{
	DO_MAP,
	PARAMS,
	SKIP,
	EXIT,
}	t_action_pars;

typedef enum e_tile
{
	SPACE,
	FLOOR,
	WALL,
	NO,
	EA,
	SO,
	WE,
	TEMP,
}	t_tile;

typedef enum e_token
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR_COLOR,
	CEILING_COLOR,
	UNKOWN,
}	t_token;

typedef struct s_texture
{
	mlx_texture_t	*north_wall;
	mlx_texture_t	*south_wall;
	mlx_texture_t	*west_wall;
	mlx_texture_t	*east_wall;
}	t_texture;

typedef struct s_assets
{
	char		*north_texture_path;
	char		*south_texture_path;
	char		*west_texture_path;
	char		*east_texture_path;
	t_texture	texture;
	bool		floor;
	bool		ceiling;
	uint32_t	col_floor;
	uint32_t	col_ceiling;
}	t_assets;

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_map
{
	char		**str_map;
	t_tile		**grid;
	bool		player;
	int			px;
	int			py;
	int			height;
	int			width;
	t_assets	assets;

}	t_map;

typedef struct s_draw
{
	double	wallx;
	int		texx;
	int		texy;
	int		lh;
	int		start;
	int		end;
}	t_draw;

typedef struct s_raycast_info
{
	t_vect	dir;
	t_vect	start;
	t_vect	hit_pos;
	int		side;
	float	perpwalldist;
}	t_raycast_info;

typedef struct s_raycast
{
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	float	sidedistx;
	float	sidedisty;
	float	deltadistx;
	float	deltadisty;
	float	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	t_vect	hit_pos;
}	t_raycast;

typedef struct s_player
{
	t_vect	dir;
	t_vect	pos;
	t_vect	c_plane;
	float	move_speed;
	float	turn_speed;
	int		head_pitch;
}	t_player;

typedef struct s_main
{
	t_player	player;
	t_map		map;
	mlx_t		*window;
	mlx_image_t	*image;
	float		fov;
	float		render_distance;
	double		prev_mousey;
	double		prev_mousex;
	int			mouse_controls;
	int			fd;
}	t_main;

typedef bool	(*t_func) (t_assets *, char *);

bool			parser(char *map_config, t_main *main);
bool		    open_file(char *path, t_main *main);
bool   			read_file(char *map_config, t_main *main);
bool			setup_map(t_main *main);
bool			validate_map(t_main *main);
bool			check_assets_order(char **str_map);
bool			extension_check(char *map_path);
void			set_tiles(t_map *map);


bool			valid_map_char(char c);
bool			valid_map_str(char *str);
int				map_start_index(char **map);
bool			determine_map_height(t_map *map);
bool			determine_map_width(t_map *map);

bool			parse_assets(t_assets *elements, char **str_map);

uint32_t		get_rgba(int r, int g, int b, int a);
void			error_msg(const char *str, t_main *main);

bool			north_parse(t_assets *texture, char *path);
bool			south_parse(t_assets *texture, char *path);
bool			east_parse(t_assets *texture, char *path);
bool			west_parse(t_assets *texture, char *path);
bool			ceiling_parse(t_assets *element, char *path);
bool			floor_parse(t_assets *element, char *path);


bool			game_init(t_main *main);


bool			game_loop(t_main *main);
void			game_controls(t_main *main);


t_vect			rotate_vector(t_vect vec, float angle);


bool			game_end(t_main *main);


t_vect			move_vector(t_main *main);
void			hitbox_check(t_main *main, t_vect pos, t_vect move_vec);
void			update_mouse(double xdelta, double ydelta, void *param);
void			toggle_hook(mlx_key_data_t keydata, void *param);


void			draw_wall(uint32_t x, t_raycast_info r,
					t_main *main, mlx_texture_t *text);
mlx_texture_t	*get_texture(t_raycast_info *r, t_texture *textures);
void			draw_floor_and_ceiling(t_main *main);
void			render_single_frame(t_main *main);
t_raycast_info	cast_ray(t_vect pos, t_vect dir, t_map map);
void			draw_line(mlx_image_t *img,
					t_vect p1, t_vect p2, unsigned int color);

void			set_distance(t_raycast *r);
void			set_hit_position(t_raycast *r, t_vect pos, t_vect raydir);


t_vect			normalize_vec(t_vect vec);

//parsing mess
void			error_exit(char *message);
void			double_free(char **str);
void		*ptr_check(void *ptr);
int			strlen_no_ws_end(char *str);
t_action_pars	look_for_action(char *line, t_main *main);
char		*remove_nl(char *line);
void	do_params(t_main *main, char *line);
int		calc_matrix(t_main *main);
t_token_pars	check_token(char *line);
int	open_fd(char *path);
int		ft_isspace(int c);
void	ft_2dfree(char **str);
int		ft_2d_arrlen(char **str);
char	*remove_nl(char *line);
char	*strjoin_free(char *to_free, char *str);
bool	width_update(t_main *main, char *line);
bool	extension_check(char *map_path);
bool	open_file(char *path, t_main *main);
int		ft_2d_arrlen(char **str);
void	ft_2dfree(char **str);
int		ft_isspace(int c);
int		double_strlen(char **arr);
char	**get_rgb(char **args);
#endif

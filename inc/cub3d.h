#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# ifdef __APPLE__				
#  define WIDTH 2400
#  define HEIGHT 1350
# elif defined(__linux__)	
#  define WIDTH 1500
#  define HEIGHT 850
# endif

typedef enum e_token
{
	EMPTY_LINE,
	MAP,
	INFO,
	ERROR,
}	t_token;

typedef enum e_action
{
	DO_MAP,
	PARAMS,
	SKIP,
	EXIT,
}	t_action;

typedef enum e_direction
{
	N,
	E,
	S,
	W,
}	t_direction;

typedef enum e_params
{
	FLOOR,
	CEILING,
	NO,
	EA,
	SO,
	WE,
}	t_params;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point		*position;
	char		direction;
}	t_player;

typedef struct s_wall
{
	char	*path;
}	t_wall;

typedef struct s_main
{
	mlx_t		*window;
	mlx_image_t	*image;
	char		**map;
	int			height;
	int			width;
	t_wall		*no;
	t_wall		*so;
	t_wall		*we;
	t_wall		*ea;
	t_rgb		*floor;
	t_rgb		*ceiling;
	t_player	*player;
	int			fd;
}	t_main;

void		scan_map(char **argv, t_main	*main);
void		error_exit(char *message);
void		double_free(char **str);
void		*ptr_check(void *ptr);
int			double_strlen(char **arr);
int			not_number(char *color);
int			invalid_color(char *color);
int			comma_check(char *color);
char		**get_rgb(char **args);
void		do_floor(t_main *main, char **args);
void		do_no_wall(t_main *main, char **args);
void		do_so_wall(t_main *main, char **args);
void		do_we_wall(t_main *main, char **args);
void		do_ea_wall(t_main *main, char **args);
int			ft_isspace(int c);
void		print_token(t_token token);
void		print_action(t_action action);
char		*strtrim_space_col(char	**str, int x, int height);
char		*strtrim_space_row(char *s1);
char		*concat_columns(char **str, int start, int end, int x);
char		*strjoin_free(char *to_free, char *str);
char		*add_extra_spaces(char *line, int len);
char		*remove_sufix_whitespace(char *str);
t_action	look_for_action(char *line, t_main *main);
char		*remove_nl(char *line);
t_token		check_token(char *line);
char		*remove_nl(char *line);
int			open_fd(char *path);
void		check_borders(char **map, int height);
int			strlen_no_ws_end(char *str);
void		fill_map(t_main *main, char *line);
void		check_player(t_main *main);
void		do_ceiling(t_main *main, char **args);

#endif
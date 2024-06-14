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
	MATRIX,
	INFO,
	ERROR,
} t_token;

typedef enum e_action
{
	DO_MAP,
	PARAMS,
	SKIP,
	EXIT,
} t_action;

typedef enum e_direction
{
	N,
	E,
	S,
	W,
} t_direction;

typedef enum e_params
{
	FLOOR,
	CEILING,
	NO,
	EA,
	SO,
	WE,
} t_params;

typedef struct s_rgb
{
	int	R;
	int	G;
	int	B;
} t_rgb;

typedef struct s_point
{
	float	x;
	float	y;
} t_point;

typedef struct s_player
{
	t_point		*position;
	t_direction	direction;
} t_player;

typedef struct s_wall
{
	char	*path;
} t_wall;

typedef struct s_main
{
	mlx_t		*window;
	mlx_image_t	*image;
	char		**map;
	t_wall		*NO;
	t_wall		*SO;
	t_wall		*WE;
	t_wall		*EA;
	t_rgb		*floor;
	t_rgb		*ceiling;
	int			fd;
} t_main;

void	scan_map(char **argv, t_main	*main);
void	error_exit(char *message);
void	double_free(char **str);
void	*ptr_check(void *ptr);
int		double_strlen(char **arr);
t_main	*init_main(void);

#endif
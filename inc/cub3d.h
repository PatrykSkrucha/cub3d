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

typedef enum s_token
{
	EMPTY_LINE,
	MATRIX,
	INFO,
	ERROR,
} t_token;

typedef enum s_action
{
	MAP,
	PARAMS,
} t_action;

typedef struct s_rgb
{
	int	R;
	int	G;
	int	B;
} t_rgb;

typedef struct s_main
{
	mlx_t		*window;
	mlx_image_t	*image;
	char		**map;
	int			NO;
	int			SO;
	int			WE;
	int			EA;
	t_rgb		*floor;
	t_rgb		*ceiling;
} t_main;

void	scan_map(char **argv, t_main	*main);
void	error_exit(char *message);
void	double_free(char **str);

#endif
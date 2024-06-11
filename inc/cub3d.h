#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# ifdef __APPLE__				
#  define WIDTH 2400
#  define HEIGHT 1350
# elif defined(__linux__)	
#  define WIDTH 1500
#  define HEIGHT 850
# endif

typedef struct s_main
{
	mlx_t			*window;
	mlx_image_t		*image;
	

} t_main;

#endif
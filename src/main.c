#include "../inc/cub3d.h"

t_main	*init_main(void)
{
	t_main	*main;

	main = ft_calloc(1, sizeof(t_main));
	if (!main)
		error_exit("Malloc error");
	main->window = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	main->image = mlx_new_image(main->window, WIDTH, HEIGHT);
	main->floor = ft_calloc(1, sizeof(t_rgb));
	main->ceiling = ft_calloc(1, sizeof(t_rgb));
	return (main);
}

int main(int argc, char **argv)
{
	t_main	*main;

	main = init_main();
	scan_map(++argv, main);
	printf("EA: 0? %i\n", main->EA);
	if (argc < 2)
	{
		ft_putstr_fd("Error\nProvide path to map\n", 2);
		return (1);
	}
	
	
	return (0);
}
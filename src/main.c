#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	t_main	*main;

	main = init_main();
	if (argc < 2)
	{
		ft_putstr_fd("Error\nProvide path to map\n", 2);
		return (1);
	}
	scan_map(++argv, main);
	return (0);
}

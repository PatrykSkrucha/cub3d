#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc < 2)
	{
		ft_putstr_fd("Error\nProvide path to map\n", 2);
		return (1);
	}
	check_size(argv[1]);
	main = ptr_check(ft_calloc(1, sizeof(t_main)));
	scan_map(++argv, main);
	return (0);
}

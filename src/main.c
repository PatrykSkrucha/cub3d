#include "../inc/cub3d.h"

void	check_size(char *str)
{
	if (ft_strlen(str) < 4)
		error_exit("Map must have extension .cub");
	while (ft_strlen(str) > 4)
		str++;
	if (ft_strncmp(str, ".cub", 3))
		error_exit("Map must have extension .cub");
}

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

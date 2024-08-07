#include "../inc/cub3d.h"

void	do_floor(t_main *main, char **args)
{
	char	**rgb;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map floor");
	if (main->floor)
		error_exit("Error while parsing the map floor");
	main->floor = ptr_check(ft_calloc(1, sizeof(t_rgb)));
	rgb = get_rgb(args);
	main->floor->r = ft_atoi(rgb[0]);
	main->floor->g = ft_atoi(rgb[1]);
	main->floor->b = ft_atoi(rgb[2]);
	double_free(rgb);
}

void	do_no_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->no)
		error_exit("Error while parsing the map no wall");
	main->no = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->no->path = ptr_check(ft_strdup(args[1]));
}

void	do_so_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map so wall");
	if (main->so)
		error_exit("Error while parsing the map so wall");
	main->so = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->so->path = ptr_check(ft_strdup(args[1]));
}

void	do_we_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map we wall");
	if (main->we)
		error_exit("Error while parsing the map we wall");
	main->we = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->we->path = ptr_check(ft_strdup(args[1]));
}

void	do_ea_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map ea wall");
	if (main->ea)
		error_exit("Error while parsing the map ea wall");
	main->ea = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->ea->path = ptr_check(ft_strdup(args[1]));
}

#include "../inc/cub3d.h"

void	do_floor(t_main *main, char **args)
{
	char	**rgb;

	if (double_strlen(args) != 2) //must contain only C and RGB color (e.g. C 99,99,99)
		error_exit("Error while parsing the map");
	if (main->floor)
		error_exit("Error while parsing the map");
	main->floor = ptr_check(ft_calloc(1, sizeof(t_rgb)));
	rgb = get_rgb(args);
	main->floor->R = ft_atoi(rgb[0]);
	main->floor->G = ft_atoi(rgb[1]);
	main->floor->B = ft_atoi(rgb[2]);
	double_free(rgb);
}

void	do_no_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2) //must contain only WALL and path (e.g. EA img/a)
		error_exit("Error while parsing the map");
	if (main->NO)
		error_exit("Error while parsing the map");
	main->NO = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->NO->path = ptr_check(ft_strdup(args[1])); //still don't know if path is valid
}
void	do_so_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2) //must contain only WALL and path (e.g. EA img/a)
		error_exit("Error while parsing the map");
	if (main->SO)
		error_exit("Error while parsing the map");
	main->SO = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->SO->path = ptr_check(ft_strdup(args[1])); //still don't know if path is valid
}
void	do_we_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2) //must contain only WALL and path (e.g. EA img/a)
		error_exit("Error while parsing the map");
	if (main->WE)
		error_exit("Error while parsing the map");
	main->WE = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->WE->path = ptr_check(ft_strdup(args[1])); //still don't know if path is valid
}
void	do_ea_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2) //must contain only WALL and path (e.g. EA img/a)
		error_exit("Error while parsing the map");
	if (main->EA)
		error_exit("Error while parsing the map");
	main->EA = ptr_check(ft_calloc(1, sizeof(t_wall)));
	main->EA->path = ptr_check(ft_strdup(args[1])); //still don't know if path is valid
}
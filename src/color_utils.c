#include "../inc/cub3d.h"

int	not_number(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
		{

			printf("not number? >%c<\n", color[i]);

			return (1);
		}
		i++;
	}
	return (0);
}

int	invalid_color(char *color)
{
	if (ft_atoi(color) > 255)
		return (1);
	return (0);
}

int	comma_check(char *color)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (color[i])
	{
		if (color[i] == ',')
			counter++;
		i++;
	}
	if (counter != 2)
		return (1);
	return (0);
}

char	**get_rgb(char **args)
{
	char	**rgb;
	int		i;

	i = 0;
	if (comma_check(args[1]))
		error_exit("Error while parsing the map COMMA");
	rgb = ptr_check(ft_split(args[1], ','));
	if (double_strlen(rgb) != 3)  //here only R, G, B
		error_exit("Error while parsing the map");
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3 || not_number(rgb[i]) || invalid_color(rgb[i]))
			error_exit("Error while parsing the map");
		i++;
	}
	return (rgb);
}
#include "../inc/cub3d.h"

int	strlen_no_ws_end(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (!ft_isspace(str[i]))
			break ;
		i--;
	}
	return (i + 1);
}

void	fill_map(t_main *main, char *line)
{
	static int	i = -1;
	char		*line_no_nl;


	line_no_nl = remove_nl(line);
	line_no_nl = remove_sufix_whitespace(line_no_nl);
	if (line_no_nl)
		line_no_nl = add_extra_spaces(line_no_nl, main->width);
	i++;
	if (!line)
	{
		main->map[i] = NULL;
		return ;
	}
	else
		main->map[i] = ptr_check(ft_strdup(line_no_nl));
	free(line_no_nl);
}

void	check_player(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	while (main->map[i])
	{
		j = 0;
		while (main->map[i][j])
		{
			if (ft_strchr("NSEA", main->map[i][j]))
			{
				if (main->player)
					error_exit("It's a single player game.");
				main->player = ptr_check(ft_calloc(1, sizeof(t_player)));
				main->player->position = ptr_check(ft_calloc(1, sizeof(t_point)));
				main->player->position->x = j;
				main->player->position->y = i;
				main->player->direction = main->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (!main->player)
		error_exit("Player not found.");
}

void	do_ceiling(t_main *main, char **args)
{
	char	**rgb;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map ceiling");
	if (main->ceiling)
		error_exit("Error while parsing the map ceiling");
	main->ceiling = ptr_check(ft_calloc(1, sizeof(t_rgb)));
	rgb = get_rgb(args);
	main->ceiling->r = ft_atoi(rgb[0]);
	main->ceiling->g = ft_atoi(rgb[1]);
	main->ceiling->b = ft_atoi(rgb[2]);
	double_free(rgb);
}

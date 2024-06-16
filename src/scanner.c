#include "../inc/cub3d.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			printf("here return char: >>%c<<", line[i]);
			return (0);
		}
		i++;
	}
	printf("empty line\n");
	return (1);
}

int check_line_info(char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	return (0);
}

int	check_for_matrix(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEA", line[i]))
			error_exit("Error while parsing the map.");
		i++;
	}
	return (1);
}

char	*remove_nl(char *line)
{
	char	*str;
	int		i;

	if (!line)
		return (NULL);
	if (!ft_strrchr(line, '\n'))
		return (ft_strdup(line));
	i = ft_strlen(line);
	if ((i == 1  && line[0] == '\n') || i == 0) //if there's only a new line or empty string
		return (NULL);
	str = ptr_check(ft_calloc(i - 1, sizeof(char)));
	ft_strlcpy(str, line, i);
	return (str);
}

static t_token	check_token (char *line)
{
	char	*str;

	line = ft_strtrim(line, " ");
	str = remove_nl(line);
	if (!str)
		return (free(str), EMPTY_LINE);
	if (check_line_info(str))
		return (free(str), INFO);
	if (check_for_matrix(str))
		return (free(str), MAP);
	return (free(str), ERROR);
}

t_action	look_for_action(t_token token, t_action	expected_move)
{
	if (token == EMPTY_LINE && expected_move == PARAMS)
		return (SKIP);
	if (token == EMPTY_LINE && expected_move == DO_MAP)
		return (SKIP);
	if (token == MAP && expected_move == DO_MAP)
		return (DO_MAP);
	if (token == MAP && expected_move == PARAMS)
		return (EXIT);
	if (token == INFO && expected_move == DO_MAP)
		return (EXIT);
	if (token == INFO && expected_move == PARAMS)
		return (PARAMS);
	if (token == ERROR)
		return (EXIT);
	return (DO_MAP);
}

t_action what_to_do(t_main *main)
{
	//if ceiling, floor or walls doesn't exist we have to get info about these variables first
	if (!main->ceiling || !main->floor || !main->NO || !main->EA || !main->SO || !main->EA)
		return (PARAMS);
	return (DO_MAP); //if we have all parameters done we have to do map parsing
}

void	alloc_matrix(char *path, t_main *main)
{
	t_token	token;
	t_token	prev_token;
	char	*line;
	int		i;
	bool	matrix_check;
	
	i = 0;
	matrix_check = false;
	main->fd = open(path, O_RDONLY);
	if (main->fd == -1)
	{
		close(main->fd);
		error_exit("Can't access the map");
	}
	prev_token = MAP;
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		token = check_token(line);
		if (prev_token == EMPTY_LINE && token == MAP && matrix_check)
			error_exit("Error while parsing the map. Empty line alloc matrix");
		if (token == MAP)
		{
			if (main->width < (int)ft_strlen(line) - 1)
				main->width = ft_strlen(line) - 1;
			matrix_check = true;
			i++;
		}
		prev_token = token;
	}
	close(main->fd);
	main->map = ptr_check(ft_calloc(i + 1, sizeof(char*)));
	main->height = i;
}



t_params	what_params(char *line)
{
	if (!ft_strncmp(line, "C", ft_strlen(line)))
		return (CEILING);
	if (!ft_strncmp(line, "F", ft_strlen(line)))
		return (FLOOR);
	if (!ft_strncmp(line, "NO", ft_strlen(line)))
		return (NO);
	if (!ft_strncmp(line, "SO", ft_strlen(line)))
		return (SO);
	if (!ft_strncmp(line, "WE", ft_strlen(line)))
		return (WE);
	if (!ft_strncmp(line, "EA", ft_strlen(line)))
		return (EA);
	return (-1);
}

void	do_ceiling(t_main *main, char **args)
{
	char	**rgb;

	if (double_strlen(args) != 2) //must contain only C and RGB color (e.g. C 99,99,99)
		error_exit("Error while parsing the map");
	if (main->ceiling)
		error_exit("Error while parsing the map");
	main->ceiling = ptr_check(ft_calloc(1, sizeof(t_rgb)));
	rgb = get_rgb(args);
	main->ceiling->R = ft_atoi(rgb[0]);
	main->ceiling->G = ft_atoi(rgb[1]);
	main->ceiling->B = ft_atoi(rgb[2]);
	double_free(rgb);
}


void	do_params(t_main *main, char *line)
{
	char		**args;
	t_params	params;
	char		*line_no_nl;

	line_no_nl = remove_nl(line);
	args = ptr_check(ft_split(line_no_nl, ' '));
	params = what_params(args[0]);
	if (params == CEILING)
		do_ceiling(main, args);
	if (params == FLOOR)
		do_floor(main, args);
	if (params == NO)
		do_no_wall(main, args);
	if (params == SO)
		do_so_wall(main, args);
	if (params == WE)
		do_we_wall(main, args);
	if (params == EA)
		do_ea_wall(main, args);
	double_free(args);
}

char	*strjoin_free(char *to_free, char *str)
{
	char	*new_str;

	new_str = ptr_check(ft_strjoin(to_free, str));
	if (to_free)
		free(to_free);
	return (new_str);
}

char	*add_extra_spaces(char *line, int len)
{
	int		i;
	char	*str;

	if ((int)ft_strlen(line) == len)
		return (line);
	i = len - (int)ft_strlen(line);
	str = ptr_check(ft_strdup(line));
	free(line);
	while (i > 0)
	{
		str = ptr_check(strjoin_free(str, " "));
		i--;
	}
	return (str);
}

void	fill_map(t_main *main, char *line)
{
	static int	i = -1;
	char		*line_no_nl;


	line_no_nl = remove_nl(line);
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

int	find_first_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			break ;
		i++;
	}
	return (i);
}

int	find_last_char(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (!ft_isspace(line[i]))
			break ;
		i--;
	}
	return (i);
}

int	strlen_no_ws(char *str)
{
	int	i;

	i = find_last_char(str) - find_first_char(str);
	if (i < 0)
		return (0);
	return (i);
}

void	check_r_l_walls(int height, int width, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			while (x < width && ft_isspace(map[y][x]))
				x++;
			if (x < width && map[y][x] != '1')
			{
				printf("x: %i, y: %i", x, y);
				error_exit("Map must be closed. left side");
			}
			while (x < width && !ft_isspace(map[y][x]))
				x++;
			if (x <= width  && map[y][x - 1] != '1')
			{
				printf("x: %i, y: %i", x, y);
				error_exit("Map must be closed. right side");
			}
			x++;
		}
		y++;
	}
}
void	check_t_b_walls(int height, int width, char **map)
{
	int	y;
	int	x;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			while (y < height && ft_isspace(map[y][x]))
				y++;
			if (y < height && map[y][x] != '1')
				error_exit("Map must be closed. top side");
			while (y < height && !ft_isspace(map[y][x]))
				y++;
			if (y < height && map[y - 1][x] != '1')
				error_exit("Map must be closed. bottom side");
		}
		x++;
	}
}

void	check_borders(char **map, int height, int width)
{
	check_r_l_walls(height, width, map);
	check_t_b_walls(height, width, map);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s<\n", map[i]);
		i++;
	}
}

void scan_map(char **argv, t_main	*main)
{
	char		*line;
	t_token		token;
	t_action	action;
	t_action	expected_move;

	expected_move = PARAMS;
	alloc_matrix(argv[0], main);
	main->fd = open(argv[0], O_RDONLY);
	if (main->fd == -1)
	{
		close(main->fd);
		error_exit("Can't access the map");
	}
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		token = check_token(line);
		expected_move = what_to_do(main);
		action = look_for_action(token, expected_move);
		if (action == EXIT)
			error_exit("Error while parsing the map");
		if (action == PARAMS)
			do_params(main, line);
		if (action == DO_MAP)
			fill_map(main, line);
		free(line);
	}
	fill_map(main, NULL);
	check_borders(main->map, main->height, main->width);
	check_player(main);
	close(main->fd);
}

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

//NO, SO, WE, EA, F, C

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
	{
		// printf("empty line\n");
		return (free(str), EMPTY_LINE);
	}
	if (check_line_info(str))
	{
		// printf("info\n");
		return (free(str), INFO);
	}
	if (check_for_matrix(str))
	{
		// printf("matrix\n");
		return (free(str), MATRIX);
	}
	// printf("\n\n\n\n>>>error<<<\n\n\n\n");
	return (free(str), ERROR);
}

t_action	look_for_action(t_token token, t_action	expected_move)
{
	if (token == EMPTY_LINE && expected_move == PARAMS)
		return (SKIP);
	// if (token == EMPTY_LINE && expected_move == MAP)
	// 	return (EXIT);
	if (token == MATRIX && expected_move == MAP)
		return (MAP);
	if (token == MATRIX && expected_move == PARAMS)
		return (EXIT);
	if (token == INFO && expected_move == MAP)
		return (EXIT);
	if (token == INFO && expected_move == PARAMS)
		return (PARAMS);
	if (token == ERROR)
		return (EXIT);
	return (MAP);
}

t_action what_to_do(t_main *main)
{
	//if ceiling, floor or walls doesn't exist we have to get info about these variables first
	if (!main->ceiling || !main->floor || !main->NO || !main->EA || !main->SO || !main->EA)
		return (PARAMS);
	return (MAP); //if we have all parameters done we have to do map parsing
}

// void	alloc_matrix(char *path, t_main *main)
// {
// 	t_token	token;
// 	t_token	prev_token;
// 	char	*line;
// 	int		i;
// 	bool	matrix_check;

// 	i = 0;
// 	matrix_check = false;
// 	main->fd = open(path, O_RDONLY);
// 	if (main->fd == -1)
// 	{
// 		close(main->fd);
// 		error_exit("Can't access the map");
// 	}
// 	prev_token = MATRIX;
// 	while (1)
// 	{
// 		line = get_next_line(main->fd);
// 		if (!line)
// 			break ;
// 		token = check_token(line);
// 		if (prev_token == EMPTY_LINE && token == MATRIX && matrix_check)
// 			error_exit("Error while parsing the map.");
// 		if (token == MATRIX)
// 		{
// 			matrix_check = true;
// 			i++;
// 		}
// 		prev_token = token;
// 	}
// 	close(main->fd);
// 	main->map = ptr_check(ft_calloc(i, sizeof(char*)));
// 	printf("map height: %i\n", i);
// }

void	print_token(t_token token)
{
	const char	*type_token[] = {
		[EMPTY_LINE] = "empty line",
		[MATRIX] = "matrix",
		[INFO] = "info",
		[ERROR] = "error",
	};
	printf("token: %s\n", type_token[token]);
}

void	print_action(t_action action)
{
	const char *type_action[] = {
		[MAP] = "map",
		[PARAMS] = "params",
		[SKIP] = "skip",
		[EXIT] = "exit",
	};
	printf("action: %s\n", type_action[action]);
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

char	**get_rgb(char **args)
{
	char	**rgb;
	int		i;

	i = 0;
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

void scan_map(char **argv, t_main	*main)
{
	char		*line;
	t_token		token;
	t_action	action;
	t_action	expected_move;
	t_token		prev_token;
	bool		first_matrix;

	(void)token;
	(void)action;
	first_matrix = false;
	main->fd = open(argv[0], O_RDONLY);
	expected_move = PARAMS; //initially we have to start with filling parameters like walls, color of ceiling and floor, then handle map
	if (main->fd == -1)
	{
		close(main->fd);
		error_exit("Can't access the map");
	}
	(void)main;
	prev_token = MATRIX;
	// alloc_matrix(argv[0], main);
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		// printf("here\n");
		// line = ft_strtrim(get_next_line(fd), " ");
		//check for params()
		token = check_token(line);
		if (token == MATRIX)
			first_matrix = true;
		expected_move = what_to_do(main);
		action = look_for_action(token, expected_move);
		print_token(token);
		print_action(expected_move);
		if (prev_token == EMPTY_LINE && token == MATRIX)
			error_exit("Error while parsing the map(empty line between map)");
		//maybe somewhere before do extra scanning to know how big matrix for map must be
		if (action == EXIT)
			error_exit("Error while parsing the map");
		if (action == PARAMS)
			do_params(main, line);
		// if (action == MAP)
		// 	parse_map(main)
		if (first_matrix)
			prev_token = token;

		//action = info_or_map(main); //this here only if token != empty line  check if we can start with scanning map
		//check if token == empty line, then action != MAP, if yes, error and exit, empty lines can be placed at the end as well
		//if done do map scanning
		//check if there's only one player on the map
		//check if map is closed 
		//check for empty lines between map

		printf("%s", line);
		free(line);
	}
	close(main->fd);
}
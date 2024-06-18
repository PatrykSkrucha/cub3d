#include "../inc/cub3d.h"

void	alloc_matrix(char *path, t_main *main)
{
	t_token	token;
	t_token	prev_token;
	char	*line;
	int		i;
	bool	matrix_check;

	i = 0;
	matrix_check = false;
	main->fd = open_fd(path);
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		token = check_token(line);
		if (matrix_check && prev_token == EMPTY_LINE && token == MAP)
			error_exit("Error while parsing the map. Empty line alloc matrix");
		if (token == MAP)
		{
			if (main->width < strlen_no_ws_end(line))
				main->width = strlen_no_ws_end(line);
			matrix_check = true;
			i++;
		}
		free(line);
		prev_token = token;
	}
	close(main->fd);
	main->map = ptr_check(ft_calloc(i + 1, sizeof(char *)));
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
	else if (params == FLOOR)
		do_floor(main, args);
	else if (params == NO)
		do_no_wall(main, args);
	else if (params == SO)
		do_so_wall(main, args);
	else if (params == WE)
		do_we_wall(main, args);
	else if (params == EA)
		do_ea_wall(main, args);
	free(line_no_nl);
	double_free(args);
}

void	scan_map(char **argv, t_main	*main)
{
	char		*line;
	t_action	action;

	alloc_matrix(argv[0], main);
	main->fd = open_fd(argv[0]);
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		action = look_for_action(line, main);
		if (action == EXIT)
			error_exit("Error while parsing the map action exit");
		else if (action == PARAMS)
			do_params(main, line);
		else if (action == DO_MAP)
			fill_map(main, line);
		free(line);
	}
	fill_map(main, NULL);
	check_borders(main->map, main->height);
	check_player(main);
	close(main->fd);
}

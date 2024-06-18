#include "../inc/cub3d.h"

static int	check_line_info(char *line)
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

static int	check_for_matrix(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) && line[i] != ' ')
			error_exit("Space is only acceptable whitespace in map.");
		if (!ft_strchr(" 01NSEA", line[i]))
		{
			printf("line: %s\n", line);
			printf("char: >%c<\n", line[i]);
			error_exit("Error while parsing the map wrong char map.");
		}
		i++;
	}
	return (1);
}

t_token	check_token(char *line)
{
	char	*str;
	char	*str_trim;

	str_trim = ft_strtrim(line, " ");
	str = remove_nl(str_trim);
	free(str_trim);
	if (!str)
		return (free(str), EMPTY_LINE);
	if (check_line_info(str))
		return (free(str), INFO);
	if (check_for_matrix(str))
		return (free(str), MAP);
	return (free(str), ERROR);
}

static t_action	what_to_do(t_main *main)
{
	if (!main->ceiling || !main->floor || !main->no || !main->ea 
		|| !main->so || !main->we)
		return (PARAMS);
	return (DO_MAP);
}

t_action	look_for_action(char *line, t_main *main)
{
	t_token		token;
	t_action	expected_move;

	token = check_token(line);
	expected_move = what_to_do(main);
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

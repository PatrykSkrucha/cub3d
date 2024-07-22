/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:54:58 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:01:56 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>
#define EXTENSION_LENGTH 4

bool	extension_check(char *map_path)
{
	if (!map_path)
		return (false);
	if (ft_strlen(map_path) <= EXTENSION_LENGTH)
		return (false);
	if (ft_strncmp(map_path + ft_strlen(map_path)
			- EXTENSION_LENGTH, ".cub", 5))
		return (false);
	return (true);
}

bool    open_file(char *path, t_main *main)
{
    main->fd = open(path, O_RDONLY);
    if (main->fd < 0)
        return (false);
    return (true);
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

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

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

char	*remove_nl(char *line)
{
	char	*str;
	int		i;

	if (!line)
		return (NULL);
	if (!ft_strrchr(line, '\n'))
		return (ptr_check(ft_strdup(line)));
	i = ft_strlen(line);
	if ((i == 1 && line[0] == '\n') || i == 0)
		return (NULL);
	str = ptr_check(ft_calloc(i - 1, sizeof(char)));
	ft_strlcpy(str, line, i);
	return (str);
}

t_token_pars	check_token(char *line)
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

char	*strjoin_free(char *to_free, char *str)
{
	char	*new_str;

	new_str = ptr_check(ft_strjoin(to_free, str));
	if (to_free)
		free(to_free);
	return (new_str);
}

void	alloc_matrix(t_main *main)
{
	t_token_pars	token;
	t_token_pars	prev_token;
	char	*line;
	int		i;
	bool	matrix_check;

	i = 0;
	matrix_check = false;
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
			if (main->map.width < strlen_no_ws_end(line))
				main->map.width = strlen_no_ws_end(line);
			matrix_check = true;
			i++;
		}
		free(line);
		prev_token = token;
	}
	close(main->fd);
	main->map.str_map = ptr_check(ft_calloc(i + 1, sizeof(char *)));
	main->map.height = i;
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

char	*remove_sufix_whitespace(char *str)
{
	char	*str1;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			break ;
		i--;
	}
	str1 = ptr_check(ft_substr(str, 0, i + 1));
	free(str);
	return (str1);
}

void	fill_map(t_main *main, char *line)
{
	static int	i = -1;
	char		*line_no_nl;

	line_no_nl = remove_nl(line);
	line_no_nl = remove_sufix_whitespace(line_no_nl);
	if (line_no_nl)
		line_no_nl = add_extra_spaces(line_no_nl, main->map.width);
	i++;
	if (!line)
	{
		main->map.str_map[i] = NULL;
		return ;
	}
	else
		main->map.str_map[i] = ptr_check(ft_strdup(line_no_nl));
	free(line_no_nl);
}

bool   read_file(char *map_config, t_main *main)
{
	char			*line;
	t_action_pars	action;

	if (!open_file(map_config, main))
		return (false);
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
	close(main->fd);
	return (true);
}

bool	flood_fill_validate(t_map *map, int y, int x)
{
	bool	ret;

	ret = true;
	if (x == 0 || y == 0 || x == map->width - 1
		|| y == map->height - 1 || map->grid[y][x] == SPACE)
		return (false);
	map->grid[y][x] = TEMP;
	if (x > 0 && map->grid[y][x - 1] != WALL && map->grid[y][x - 1] != TEMP)
		ret = flood_fill_validate(map, y, x - 1);
	if (ret && x < map->width && map->grid[y][x + 1] != WALL
			&& map->grid[y][x + 1] != TEMP)
		ret = flood_fill_validate(map, y, x + 1);
	if (ret && y > 0 && map->grid[y - 1][x] != WALL
			&& map->grid[y - 1][x] != TEMP)
		ret = flood_fill_validate(map, y - 1, x);
	if (ret && y < map->height && map->grid[y + 1][x] != WALL
			&& map->grid[y + 1][x] != TEMP)
		ret = flood_fill_validate(map, y + 1, x);
	return (ret);
}

bool	validate_map(t_main *main)
{
	t_tile	p_tile;

	if (main->map.px == -1)
		return (error_msg("No Player Location\n", main), false);
	p_tile = main->map.grid[main->map.py][main->map.px];
	if (!flood_fill_validate(&main->map, main->map.py, main->map.px))
		return (error_msg("No Valid Path\n", main), false);
	set_tiles(&main->map);
	main->map.grid[main->map.py][main->map.px] = p_tile;
	return (true);
}

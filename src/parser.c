/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:06 by ncornacc          #+#    #+#             */
/*   Updated: 2024/08/21 19:18:07 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		ft_2d_arrlen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_2dfree(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

//char	*remove_nl(char *line)
//{
//	char	*str;
//	int		i;

//	if (!line)
//		return (NULL);
//	if (!ft_strrchr(line, '\n'))
//		return (ptr_check(ft_strdup(line)));
//	i = ft_strlen(line);
//	if ((i == 1 && line[0] == '\n') || i == 0)
//		return (NULL);
//	str = ptr_check(ft_calloc(i - 1, sizeof(char)));
//	ft_strlcpy(str, line, i);
//	return (str);
//}

t_token	what_params(char *line)
{
	if (!ft_strncmp(line, "C", ft_strlen(line)))
		return (CEILING_COLOR);
	if (!ft_strncmp(line, "F", ft_strlen(line)))
		return (FLOOR_COLOR);
	if (!ft_strncmp(line, "NO", ft_strlen(line)))
		return (NORTH);
	if (!ft_strncmp(line, "SO", ft_strlen(line)))
		return (SOUTH);
	if (!ft_strncmp(line, "WE", ft_strlen(line)))
		return (WEST);
	if (!ft_strncmp(line, "EA", ft_strlen(line)))
		return (EAST);
	return (-1);
}

int	double_strlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	not_number(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (1);
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
	if (double_strlen(rgb) != 3)
		error_exit("Error while parsing the map rgb");
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3 || not_number(rgb[i])
			|| invalid_color(rgb[i]))
			error_exit("Error while parsing the map rgb");
		i++;
	}
	return (rgb);
}

void	do_no_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.north_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.north_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.north_wall)
		error_exit("Error MLX NO wall");
}

void	do_so_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.south_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.south_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.south_wall)
		error_exit("Error MLX NO wall");
}

void	do_we_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.west_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.west_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.west_wall)
		error_exit("Error MLX NO wall");
}

void	do_ea_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.east_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.east_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.east_wall)
		error_exit("Error MLX NO wall");
}


void	do_floor(t_main *main, char **args)
{
	char	**rgb;
	uint32_t	col;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map floor");
	if (main->map.assets.floor)
		error_exit("Error while parsing the map floor");
	rgb = get_rgb(args);
	col = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	main->map.assets.col_floor = col;
	main->map.assets.floor = true;
	double_free(rgb);
}

void	do_ceiling(t_main *main, char **args)
{
	char		**rgb;
	uint32_t	col;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map ceiling");
	if (main->map.assets.ceiling)
		error_exit("Error while parsing the map ceiling");
	rgb = get_rgb(args);
	col = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	main->map.assets.col_ceiling = col;
	main->map.assets.ceiling = true;
	double_free(rgb);
}

void	do_params(t_main *main, char *line)
{
	char		**args;
	t_token		params;
	char		*line_no_nl;

	line_no_nl = remove_nl(line);
	args = ptr_check(ft_split(line_no_nl, ' '));
	params = what_params(args[0]);
	if (params == CEILING_COLOR)
		do_ceiling(main, args);
	else if (params == FLOOR_COLOR)
		do_floor(main, args);
	else if (params == NORTH)
		do_no_wall(main, args);
	else if (params == SOUTH)
		do_so_wall(main, args);
	else if (params == WEST)
		do_we_wall(main, args);
	else if (params == EAST)
		do_ea_wall(main, args);
	free(line_no_nl);
	double_free(args);
}

static t_action_pars	what_to_do(t_main *main)
{
	if (!main->map.assets.ceiling || !main->map.assets.floor 
		|| !main->map.assets.texture.north_wall 
		|| !main->map.assets.texture.east_wall 
		|| !main->map.assets.texture.south_wall
		|| !main->map.assets.texture.west_wall)
		return (PARAMS);
	return (DO_MAP);
}

t_action_pars	look_for_action(char *line, t_main *main)
{
	t_token_pars	token;
	t_action_pars	expected_move;

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

void	*ptr_check(void *ptr)
{
	if (!ptr)
		error_exit("Malloc failure.");
	return (ptr);
}

void	double_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*concat_columns(char **str, int start, int end, int x)
{
	char	*str2;
	int		i;

	i = 0;
	str2 = ptr_check(ft_calloc(sizeof(char), end - start + 2));
	while (start + i <= end)
	{
		str2[i] = str[start + i][x];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

static int	move_pointer_col(char **s1, int x, int y)
{
	if (y < 0 || !s1[y])
		return (0);
	if (s1[y][x] && ft_isspace(s1[y][x]))
		return (1);
	return (0);
}

static int	move_pointer(char *s1, int index)
{
	if (!s1[index])
		return (0);
	if (s1[index] && ft_isspace(s1[index]))
		return (1);
	return (0);
}

char	*strtrim_space_row(char *s1)
{
	char	*str;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
		return (s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (move_pointer(s1, start))
		start++;
	while (move_pointer(s1, end))
		end--;
	if (start >= end + 1)
		return (s1);
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}

char	*strtrim_space_col(char	**str, int x, int height)
{
	char	*str1;
	int		start;
	int		end;

	start = 0;
	end = height - 1;
	while (move_pointer_col(str, x, start))
		start++;
	while (move_pointer_col(str, x, end))
		end--;
	if (start >= end + 1)
		return (NULL);
	str1 = concat_columns(str, start, end, x);
	return (str1);
}

void	check_rows(char **map)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	while (map[i])
	{
		str = strtrim_space_row(map[i]);
		j = 0;
		while (str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the left side.");
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the right side.");
			j++;
		}
		free(str);
		i++;
	}
}

void	check_columns(int height, char **map)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (map[0][i])
	{
		str = strtrim_space_col(map, i, height);
		j = 0;
		while (str != NULL && str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on top");
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on bottom");
			j++;
		}
		if (str)
			free(str);
		i++;
	}
}

void	check_borders(char **map, int height)
{
	check_rows(map);
	check_columns(height, map);
}

void	check_player(t_main *main)
{
	int	i;
	int	j;

	i = 0;
	while (main->map.str_map[i])
	{
		j = 0;
		while (main->map.str_map[i][j])
		{
			if (ft_strchr("NSEA", main->map.str_map[i][j]))
			{
				if (main->map.player)
					error_exit("It's a single player game.");
				main->map.player = true;
			}
			j++;
		}
		i++;
	}
	if (!main->map.player)
		error_exit("Player not found.");
}

int	open_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		error_exit("Can't access the map");
	}
	return (fd);
}

bool	parser(char *map_config, t_main *main)
{
	if (!extension_check(map_config))
		return (error_msg("Invalid Map Extension]\n", main), false);
	main->fd = open_fd(map_config);
	alloc_matrix(main);
	if (!read_file(map_config, main))
		return (error_msg("Map Reading Allocation Failed\n", main), false);
	check_borders(main->map.str_map, main->map.height);
	check_player(main);
	if (!setup_map(main))
		return (false);
	if (!validate_map(main))
		return (false);
	return (true);
}

t_token	string_to_token(char *str)
{
	if (!ft_strncmp(str, "NO", 3))
		return (NORTH);
	if (!ft_strncmp(str, "SO", 3))
		return (SOUTH);
	if (!ft_strncmp(str, "WE", 3))
		return (WEST);
	if (!ft_strncmp(str, "EA", 3))
		return (EAST);
	if (!ft_strncmp(str, "F", 2))
		return (FLOOR_COLOR);
	if (!ft_strncmp(str, "C", 2))
		return (CEILING_COLOR);
	return (UNKOWN);
}

t_func	select_token(t_token token)
{
	const t_func	functions[7] = {
	[WEST] = west_parse,
	[EAST] = east_parse,
	[NORTH] = north_parse,
	[SOUTH] = south_parse,
	[FLOOR_COLOR] = floor_parse,
	[CEILING_COLOR] = ceiling_parse,
	};

	return (functions[token]);
}

bool	parse_assets(t_assets *assets, char **str_map)
{
	char			**arr;
	size_t			index;
	t_func			function;
	t_token			asset;

	index = 0;
	while (str_map[index] != NULL)
	{
		arr = ft_split(str_map[index], ' ');
		if (!arr)
			return (false);
		asset = string_to_token(arr[0]);
		if (asset != UNKOWN)
		{
			function = select_token(asset);
			if (!function(assets, arr[1]))
				return (ft_2dfree(arr), false);
		}
		ft_2dfree(arr);
		index++;
	}
	return (true);
}

bool	check_assets_order(char **str_map)
{
	size_t	i;

	i = map_start_index(str_map);
	while (str_map[i] && valid_map_str(str_map[i]))
		i++;
	while (str_map[i])
	{
		if (str_map[i][0] != '\n')
			return (false);
		i++;
	}
	return (true);
}


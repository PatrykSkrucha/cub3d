/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:06 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 16:07:49 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	do_floor(t_main *main, char **args)
{
	char		**rgb;
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

void	make_assets(t_main *main, char *line)
{
	char		**args;
	t_token		params;
	char		*line_no_nl;

	line_no_nl = remove_nl(line);
	args = ptr_check(ft_split(line_no_nl, ' '));
	params = which_asset(args[0]);
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

void   error_exit(char *message)
{
       ft_putstr_fd("Error\n", 2);
       ft_putstr_fd(message, 2);
       ft_putstr_fd("\n", 2);
       exit (1);
}

bool	parser(char *map_config, t_main *main)
{
	if (!extension_check(map_config))
		return (error_msg("Invalid map extension\n", main), false);
	if (!open_file(map_config, main))
		return (error_msg("File not accessible.\n", main), false);
	main->map.height = calc_matrix(main);
	main->map.str_map = ptr_check(ft_calloc(main->map.height + 1, \
						sizeof(char *)));
	if (!read_file(map_config, main))
		return (error_msg("Map reading allocation failed\n", main), false);
	check_borders(main->map.str_map, main->map.height);
	if (!setup_map(main))
		return (false);
	if (!validate_map(main))
		return (false);
	return (true);
}

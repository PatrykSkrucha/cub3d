/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:46:22 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 20:33:12 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_valid_char(char *line, t_main *main)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) && line[i] != ' ')
			error_exit("Space is only acceptable whitespace in map.", main);
		if (!ft_strchr(" 01NSEA", line[i]))
		{
			printf("line: %s\n", line);
			printf("char: >%c<\n", line[i]);
			error_exit("Error while parsing the map wrong char map.", main);
		}
		i++;
	}
	return (1);
}

static int	check_line_info(char *line)
{
	char	**arr;
	char	*cpy_str;

	cpy_str = ptr_check(ft_strdup(line));
	arr = ft_split(cpy_str, ' ');
	free(cpy_str);
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
	double_free(arr);
	return (0);
}

t_token_pars	check_token(char *line, t_main *main)
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
	if (check_valid_char(str, main))
		return (free(str), MAP);
	return (free(str), ERROR);
}

bool	read_file(char *map_config, t_main *main)
{
	char			*line;
	t_action_pars	action;

	close(main->fd);
	if (!open_file(map_config, main))
		return (false);
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		action = look_for_action(line, main);
		if (action == EXIT)
			error_exit("Error while parsing the map action exit", main);
		else if (action == PARAMS)
			make_assets(main, line);
		else if (action == DO_MAP)
			fill_map(main, line);
		free(line);
	}
	fill_map(main, NULL);
	close(main->fd);
	return (true);
}

bool	validate_map(t_main *main)
{
	t_tile	p_tile;

	if (main->map.px == -1)
		return (error_msg("No Player Location\n", main), false);
	p_tile = main->map.grid[main->map.py][main->map.px];
	set_tiles(&main->map);
	main->map.grid[main->map.py][main->map.px] = p_tile;
	return (true);
}

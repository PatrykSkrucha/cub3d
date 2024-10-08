/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:06 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 18:56:24 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

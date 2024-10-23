/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:06 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/22 16:08:40 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_rows(t_main *main)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	while (main->map.str_map[i])
	{
		str = strtrim_space_row(main->map.str_map[i]);
		j = 0;
		while (str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the left side.", main);
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the right side.", main);
			j++;
		}
		free(str);
		i++;
	}
}

void	check_columns(t_main *main)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (main->map.str_map[0][i])
	{
		str = strtrim_space_col(main->map.str_map, i, main->map.height);
		j = 0;
		while (str != NULL && str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on top", main);
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on bottom", main);
			j++;
		}
		if (str)
			free(str);
		i++;
	}
}

void	check_borders(t_main *main)
{
	check_rows(main);
	check_columns(main);
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
			if (ft_strchr("NSEW", main->map.str_map[i][j]))
			{
				if (main->map.player)
					error_exit("It's a single player game.", main);
				main->map.player = true;
			}
			j++;
		}
		i++;
	}
	if (!main->map.player)
		error_exit("Player not found.", main);
}

bool	parser(char *map_config, t_main *main)
{
	if (!extension_check(map_config))
		return (error_msg("Invalid map extension\n", main), false);
	if (!open_file(map_config, main))
		return (error_msg("File not accessible.\n", main), false);
	main->map.height = calc_matrix(main);
	if (main->map.height == -1)
		return (error_msg("Error while parsing the map. Empty line\n", main), \
				false);
	main->map.str_map = ptr_check(ft_calloc(main->map.height + 1, \
						sizeof(char *)));
	if (!read_file(map_config, main))
		return (error_msg("Map reading allocation failed\n", main), false);
	check_borders(main);
	if (!setup_map(main))
		return (false);
	if (!validate_map(main))
		return (false);
	return (true);
}

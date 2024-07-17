/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:55:06 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:02:12 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	parser(char *map_config, t_main *main)
{
	int	file;

	if (!extension_check(map_config))
		return (error_msg("Invalid Map Extension]\n", main), false);
	if (!open_file(map_config, &file))
		return (error_msg("Cant Open Map\n", main), false);
	if (!read_file(file, &main->map))
		return (error_msg("Map Reading Allocation Failed\n", main), false);
	if (!check_assets_order(main->map.str_map))
		return (error_msg("Map is not the last asset!\n", main), false);
	if (!parse_assets(&(main->map.assets), main->map.str_map))
		return (error_msg("Parse Elements Allocation Failed\n", main), false);
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_parse2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:52:52 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 20:34:18 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	do_floor(t_main *main, char **args)
{
	char		**rgb;
	uint32_t	col;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map floor", main);
	if (main->map.assets.floor)
		error_exit("Error while parsing the map floor", main);
	rgb = get_rgb(args, main);
	col = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	main->map.assets.col_floor = col;
	main->map.assets.floor = true;
	double_free(rgb);
}

static void	do_ceiling(t_main *main, char **args)
{
	char		**rgb;
	uint32_t	col;

	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map ceiling", main);
	if (main->map.assets.ceiling)
		error_exit("Error while parsing the map ceiling", main);
	rgb = get_rgb(args, main);
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

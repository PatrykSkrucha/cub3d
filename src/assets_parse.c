/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:44 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 16:10:18 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
		error_exit("Error MLX SO wall");
}

void	do_we_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.west_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.west_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.west_wall)
		error_exit("Error MLX WE wall");
}

void	do_ea_wall(t_main *main, char **args)
{
	if (double_strlen(args) != 2)
		error_exit("Error while parsing the map no wall");
	if (main->map.assets.texture.east_wall)
		error_exit("Error while parsing the map no wall");
	main->map.assets.texture.east_wall = mlx_load_png(args[1]);
	if (!main->map.assets.texture.east_wall)
		error_exit("Error MLX EA wall");
}

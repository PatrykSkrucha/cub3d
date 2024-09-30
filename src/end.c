/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:05 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:01:08 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>

void	mlx_end(t_main *main)
{
	if (main->image != NULL)
		mlx_delete_image(main->window, main->image);
}

bool	game_end(t_main *main)
{
	if (main->window != NULL)
		mlx_end(main);
	if (main->map.assets.texture.east_wall != NULL)
		mlx_delete_texture(main->map.assets.texture.east_wall);
	if (main->map.assets.texture.west_wall != NULL)
		mlx_delete_texture(main->map.assets.texture.west_wall);
	if (main->map.assets.texture.north_wall != NULL)
		mlx_delete_texture(main->map.assets.texture.north_wall);
	if (main->map.assets.texture.south_wall != NULL)
		mlx_delete_texture(main->map.assets.texture.south_wall);
	ft_2dfree(main->map.str_map);
	ft_2dfree((char **)main->map.grid);
	return (true);
}

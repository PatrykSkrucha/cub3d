/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 14:01:57 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 14:10:33 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void	window_end(t_main *main)
{
	if (main->image != NULL)
		mlx_delete_image(main->window, main->image);
}

bool	end_program(t_main *main)
{
	if (main->window != NULL)
		window_end(main);
	if (main->map.assets.textures.ea != NULL)
		mlx_delete_texture(main->map.assets.textures.ea);
	if (main->map.assets.textures.we != NULL)
		mlx_delete_texture(main->map.assets.textures.we);
	if (main->map.assets.textures.no != NULL)
		mlx_delete_texture(main->map.assets.textures.no);
	if (main->map.assets.textures.so != NULL)
		mlx_delete_texture(main->map.assets.textures.so);
	matrix_free(main->map.map);
	matrix_free((char **)main->map.grid);
	return (true);
}

void	hit_check(t_main *main, t_vect position, t_vect move)
{
	int	add_y;
	int	add_x;

	add_x = 1;
	add_y = 1;
	if (main->map.grid[(int)(position.y + 0.1)][(int)(position.x + 0.1 + move.x)] == WALL)
		add_x = 0;
	if (main->map.grid[(int)(position.y - 0.1)][(int)(position.x + 0.1 + move.x)] == WALL)
		add_x = 0;
	if (main->map.grid[(int)(position.y + 0.1)][(int)(position.x - 0.1 + move.x)] == WALL)
		add_x = 0;
	if (main->map.grid[(int)(position.y - 0.1)][(int)(position.x - 0.1 + move.x)] == WALL)
		add_x = 0;
	if (main->map.grid[(int)(position.y + 0.1 + move.y)][(int)(position.x + 0.1)] == WALL)
		add_y = 0;
	if (main->map.grid[(int)(position.y - 0.1 + move.y)][(int)(position.x + 0.1)] == WALL)
		add_y = 0;
	if (main->map.grid[(int)(position.y + 0.1 + move.y)][(int)(position.x - 0.1)] == WALL)
		add_y = 0;
	if (main->map.grid[(int)(position.y - 0.1 + move.y)][(int)(position.x - 0.1)] == WALL)
		add_y = 0;
	if (add_y == 1)
		main->player.position.y += move.y;
	if (add_x == 1)
		main->player.position.x += move.x;
}

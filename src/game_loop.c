/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:13 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 12:41:56 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include <cub3d.h>
#include <stdint.h>

bool	update_image_scale(t_main *main)
{
	if ((uint32_t)main->window->width != main->image->width
		|| (uint32_t)main->window->height != main->image->height)
	{
		mlx_delete_image(main->window, main->image);
		main->image = mlx_new_image(main->window, main->window->width, main->window->height);
		mlx_image_to_window(main->window, main->image, 0, 0);
		main->image->instances[0].z = 0;
		return (true);
	}
	return (false);
}

void	game_tick(void *param)
{
	t_main	*main;

	main = (t_main *)param;
	if (update_image_scale(main))
		return ;
	game_controls(main);
	render_single_frame(main);
}

bool	game_loop(t_main *main)
{
	if (!mlx_loop_hook(main->window, game_tick, (void *)main))
		return (error_msg("Mlx Loop hook failed\n", main), false);
	mlx_cursor_hook(main->window, update_mouse, (void *)main);
	mlx_key_hook(main->window, toggle_hook, (void *)main);
	mlx_loop(main->window);
	return (true);
}

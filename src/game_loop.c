/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 11:43:41 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/27 13:53:23 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    update_image_scale(t_main *main)
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

void    tick(void *param)
{
    t_main  *main;

    main = (t_main *)param;
    if (update_image_scale(main))
        return ;
    game_controls(main);
    render_single_frame(main);
}

bool    game_loop(t_main *main)
{
    if (!mlx_loop_hook(main->window, tick, (void *)main))
        return (error_msg("MLX loop hook has failed\n", main), false);
    mlx_cursor_hook(main->window, mouse_update, (void *)main);
    mlx_key_hook(main->window, key_hook, (void *)main);
    mlx_loop(main->window);
    return (true);
}



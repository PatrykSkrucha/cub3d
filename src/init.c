/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:10 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:01:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>
#include <stdint.h>

void	get_player_orientation(t_main *main)
{
	if (main->map.grid[main->map.py][main->map.px] == NO)
	{
		main->player.dir.x = 0;
		main->player.dir.y = -1;
	}
	else if (main->map.grid[main->map.py][main->map.px] == EA)
	{
		main->player.dir.x = 1;
		main->player.dir.y = 0;
	}
	else if (main->map.grid[main->map.py][main->map.px] == SO)
	{
		main->player.dir.x = 0;
		main->player.dir.y = 1;
	}
	else if (main->map.grid[main->map.py][main->map.px] == WE)
	{
		main->player.dir.x = -1;
		main->player.dir.y = 0;
	}
}

void	player_init(t_main *main)
{
	get_player_orientation(main);
	main->player.pos.x = main->map.px;
	main->player.pos.y = main->map.py;
	main->map.grid[main->map.py][main->map.px] = FLOOR;
	main->player.c_plane = rotate_vector(main->player.dir, 90);
	main->player.move_speed = 5;
	main->player.turn_speed = 200;
	main->player.head_pitch = 0;
}

static bool	image_init(t_main *main)
{
	main->image = mlx_new_image(main->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!main->image)
		return (false);
	if (mlx_image_to_window(main->window, main->image, 0, 0) == -1)
		return (false);
	return (true);
}

bool	game_init(t_main *main)
{
	player_init(main);
	main->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", 1);
	if (main->window == NULL)
		return (error_msg("Mlx initilization failed\n", main), false);
	if (!image_init(main))
		return (error_msg("Image initilization failed\n", main), false);
	main->fov = 3.0;
	main->render_distance = 10;
	main->map.grid[main->map.py][main->map.px] = FLOOR;
	return (true);
}

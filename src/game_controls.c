/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:01 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 16:14:46 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	update_mouse(double xpos, double ypos, void *param)
{
	t_main	*main;

	main = (t_main *)param;
	if (main->mouse_controls == 0)
		return ;
	main->player.dir = rotate_vector(main->player.dir,
			(main->window->delta_time * (xpos - main->prev_mousex)
				* (main->player.turn_speed / 12)));
	main->player.c_plane = rotate_vector(main->player.c_plane,
			(main->window->delta_time * (xpos - main->prev_mousex)
				* (main->player.turn_speed / 12)));
	main->player.head_pitch -= main->window->delta_time
		* (ypos - main->prev_mousey) * 150;
	if (main->player.head_pitch > (int)(main->image->height / 2))
		main->player.head_pitch = (int)(main->image->height / 2);
	else if (main->player.head_pitch < -(int)(main->image->height / 2))
		main->player.head_pitch = -(int)(main->image->height / 2);
	main->prev_mousey = main->image->height / 2;
	main->prev_mousex = main->image->width / 2;
	mlx_set_mouse_pos(main->window, main->image->width \
		/ 2, main->image->height / 2);
}

static void	update_player_direction(t_main *main)
{
	if (mlx_is_key_down(main->window, MLX_KEY_RIGHT))
	{
		main->player.dir = rotate_vector(main->player.dir,
				main->window->delta_time * main->player.turn_speed);
		main->player.c_plane = rotate_vector(main->player.c_plane,
				main->window->delta_time * main->player.turn_speed);
	}
	if (mlx_is_key_down(main->window, MLX_KEY_LEFT))
	{
		main->player.dir = rotate_vector(main->player.dir,
				main->window->delta_time * -main->player.turn_speed);
		main->player.c_plane = rotate_vector(main->player.c_plane,
				main->window->delta_time * -main->player.turn_speed);
	}
	if (mlx_is_key_down(main->window, MLX_KEY_UP)
		&& main->player.head_pitch < (int)(main->image->height / 2))
		main->player.head_pitch += main->window->delta_time * 300;
	if (mlx_is_key_down(main->window, MLX_KEY_DOWN)
		&& main->player.head_pitch > -(int)(main->image->height / 2))
		main->player.head_pitch -= main->window->delta_time * 300;
}

void	toggle_hook(mlx_key_data_t keydata, void *param)
{
	t_main	*main;

	main = (t_main *)param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		main->mouse_controls = (main->mouse_controls * -1) + 1;
		if (main->mouse_controls)
			mlx_set_cursor_mode(main->window, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(main->window, MLX_MOUSE_NORMAL);
	}
}

void	cub_movement_check(t_main *main)
{
	t_vect			move_vec;
	t_vect			pos;
	t_raycast_info	r;

	move_vec = move_vector(main);
	if (move_vec.x == 0 && move_vec.y == 0)
		return ;
	move_vec = normalize_vec(move_vec);
	pos = main->player.pos;
	r = cast_ray(pos, move_vec, main->map);
	if (r.perpwalldist < main->window->delta_time * main->player.move_speed)
	{
		move_vec.x = move_vec.x * r.perpwalldist;
		move_vec.y = move_vec.y * r.perpwalldist;
	}
	else if (r.perpwalldist > main->window->delta_time \
		* main->player.move_speed)
	{
		move_vec.x = move_vec.x * main->window->delta_time \
			* main->player.move_speed;
		move_vec.y = move_vec.y * main->window->delta_time \
			* main->player.move_speed;
	}
	hitbox_check(main, pos, move_vec);
}

void	game_controls(t_main *main)
{
	if (mlx_is_key_down(main->window, MLX_KEY_ESCAPE))
		mlx_close_window(main->window);
	update_player_direction(main);
	cub_movement_check(main);
	if (mlx_is_key_down(main->window, MLX_KEY_EQUAL) && main->fov < 10)
		main->fov += 0.1;
	if (mlx_is_key_down(main->window, MLX_KEY_MINUS) && main->fov > 0.5)
		main->fov -= 0.1;
}

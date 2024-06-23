/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 11:56:42 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 14:01:39 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    mouse_update(double x_pos, double y_pos, void *param)
{
    	t_main	*main;

	main = (t_main *)param;
	if (main->mouse == 0)
		return ;
	main->player.direction = rotate_vector(main->player.direction,
			(main->window->delta_time * (x_pos - main->previous_mouse_x)
				* (main->player.rotation_speed / 12)));
	main->player.plane = rotate_vector(main->player.plane,
			(main->window->delta_time * (x_pos - main->previous_mouse_x)
				* (main->player.rotation_speed / 12)));
	main->player.turn_direction -= main->window->delta_time
		* (y_pos - main->previous_mouse_y) * 150;
	if (main->player.turn_direction > (int)(main->image->height / 2))
		main->player.turn_direction = (int)(main->image->height / 2);
	else if (main->player.turn_direction < -(int)(main->image->height / 2))
		main->player.turn_direction = -(int)(main->image->height / 2);
	main->previous_mouse_y = main->image->height / 2;
	main->previous_mouse_x = main->image->width / 2;
	mlx_set_mouse_pos(main->window, main->image->width / 2, main->image->height / 2);
}

void    key_hook(mlx_key_data_t keydata, void *param)
{
    t_main	*main;

	main = (t_main *)param;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		main->mouse = (main->mouse * -1) + 1;
		if (main->mouse)
			mlx_set_cursor_mode(main->window, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(main->window, MLX_MOUSE_NORMAL);
	}
}

static void update_player(t_main *main)
{
    if (mlx_is_key_down(main->window, MLX_KEY_RIGHT))
	{
		main->player.direction = rotate_vector(main->player.direction,
				main->window->delta_time * main->player.rotation_speed);
		main->player.plane = rotate_vector(main->player.plane,
				main->window->delta_time * main->player.rotation_speed);
	}
	if (mlx_is_key_down(main->window, MLX_KEY_LEFT))
	{
		main->player.direction = rotate_vector(main->player.direction,
				main->window->delta_time * -main->player.rotation_speed);
		main->player.plane = rotate_vector(main->player.plane,
				main->window->delta_time * -main->player.rotation_speed);
	}
	if (mlx_is_key_down(main->window, MLX_KEY_UP)
		&& main->player.turn_direction < (int)(main->image->height / 2))
		main->player.turn_direction += main->window->delta_time * 300;
	if (mlx_is_key_down(main->window, MLX_KEY_DOWN)
		&& main->player.turn_direction > -(int)(main->image->height / 2))
		main->player.turn_direction -= main->window->delta_time * 300;
}

void    move_check(t_main *main)
{
    t_vect			move_vec;
	t_vect			position;
	t_ray_data	    r;

	move_vec = move_vector(main);
	if (move_vec.x == 0 && move_vec.y == 0)
		return ;
	move_vec = normalize_vector(move_vec);
	position = main->player.position;
	r = cast_ray(position, move_vec, main->map);
	if (r.perp_wall_dist < main->window->delta_time * main->player.move_speed)
	{
		move_vec.x = move_vec.x * r.perp_wall_dist;
		move_vec.y = move_vec.y * r.perp_wall_dist;
	}
	else if (r.perp_wall_dist > main->window->delta_time * main->player.move_speed)
	{
		move_vec.x = move_vec.x * main->window->delta_time * main->player.move_speed;
		move_vec.y = move_vec.y * main->window->delta_time * main->player.move_speed;
	}
	hit_check(main, position, move_vec);
}

void    game_controls(t_main *main)
{
    if (mlx_is_key_down(main->window, MLX_KEY_ESCAPE))
		mlx_close_window(main->window);
	update_player(main);
	move_check(main);
	if (mlx_is_key_down(main->window, MLX_KEY_EQUAL) && main->fov < 10)
		main->fov += 0.1;
	if (mlx_is_key_down(main->window, MLX_KEY_MINUS) && main->fov > 0.5)
		main->fov -= 0.1;
}


float	deg_to_rad(float angle)
{
	return (angle * M_PI / 180.0);
}

t_vect	rotate_vector(t_vect vector, float angle)
{
	t_vect	vec2;
	float	rad_angle;

	rad_angle = deg_to_rad(angle);
	vec2.x = (cos(rad_angle) * vector.x) - (sin(rad_angle) * vector.y);
	vec2.y = (sin(rad_angle) * vector.x) + (cos(rad_angle) * vector.y);
	return (vec2);
}

t_vect	normalize_vector(t_vect vector)
{
	float	a;
	float	b;
	float	c;

	a = vector.x * vector.x;
	b = vector.y * vector.y;
	c = sqrt(a + b);
	vector.x = vector.x / c;
	vector.y = vector.y / c;
	return (vector);
}


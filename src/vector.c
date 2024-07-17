/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:22 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:06:22 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	add_right_vec(t_vect *move_vec, t_main *main)
{
	move_vec->x += rotate_vector(main->player.dir, 90).x;
	move_vec->y += rotate_vector(main->player.dir, 90).y;
}

static void	add_left_vec(t_vect *move_vec, t_main *main)
{
	move_vec->x -= rotate_vector(main->player.dir, 90).x;
	move_vec->y -= rotate_vector(main->player.dir, 90).y;
}

static void	add_backward_vec(t_vect *move_vec, t_main *main)
{
	move_vec->x -= main->player.dir.x;
	move_vec->y -= main->player.dir.y;
}

static void	add_forward_vec(t_vect *move_vec, t_main *main)
{
	move_vec->x += main->player.dir.x;
	move_vec->y += main->player.dir.y;
}

t_vect	move_vector(t_main *main)
{
	t_vect	move_vec;

	move_vec.x = 0;
	move_vec.y = 0;
	if (mlx_is_key_down(main->window, MLX_KEY_W))
		add_forward_vec(&move_vec, main);
	if (mlx_is_key_down(main->window, MLX_KEY_S))
		add_backward_vec(&move_vec, main);
	if (mlx_is_key_down(main->window, MLX_KEY_D))
		add_right_vec(&move_vec, main);
	if (mlx_is_key_down(main->window, MLX_KEY_A))
		add_left_vec(&move_vec, main);
	return (move_vec);
}

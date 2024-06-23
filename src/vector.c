/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 12:54:04 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 13:25:50 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	add_right_vec(t_vect *move, t_main *main)
{
	move->x += rotate_vector(main->player.direction, 90).x;
	move->y += rotate_vector(main->player.direction, 90).y;
}

static void	add_left_vec(t_vect *move, t_main *main)
{
	move->x -= rotate_vector(main->player.direction, 90).x;
	move->y -= rotate_vector(main->player.direction, 90).y;
}

static void	add_backward_vec(t_vect *move, t_main *main)
{
	move->x -= main->player.direction.x;
	move->y -= main->player.direction.y;
}

static void	add_forward_vec(t_vect *move, t_main *main)
{
	move->x += main->player.direction.x;
	move->y += main->player.direction.y;
}


t_vect move_vector(t_main *main)
{
    t_vect  move;

    move.x = 0;
    move.y = 0;
    if (mlx_is_key_down(main->window, MLX_KEY_W))
		add_forward_vec(&move, main);
	if (mlx_is_key_down(main->window, MLX_KEY_S))
		add_backward_vec(&move, main);
	if (mlx_is_key_down(main->window, MLX_KEY_D))
		add_right_vec(&move, main);
	if (mlx_is_key_down(main->window, MLX_KEY_A))
		add_left_vec(&move, main);
	return (move);
}

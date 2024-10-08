/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:18 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 20:25:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	hitbox_check(t_main *main, t_vect pos, t_vect mv)
{
	int	addy;
	int	addx;

	addx = 1;
	addy = 1;
	if (main->map.grid[(int)(pos.y + 0.1)][(int)(pos.x + 0.1 + mv.x)] == WALL)
		addx = 0;
	if (main->map.grid[(int)(pos.y - 0.1)][(int)(pos.x + 0.1 + mv.x)] == WALL)
		addx = 0;
	if (main->map.grid[(int)(pos.y + 0.1)][(int)(pos.x - 0.1 + mv.x)] == WALL)
		addx = 0;
	if (main->map.grid[(int)(pos.y - 0.1)][(int)(pos.x - 0.1 + mv.x)] == WALL)
		addx = 0;
	if (main->map.grid[(int)(pos.y + 0.1 + mv.y)][(int)(pos.x + 0.1)] == WALL)
		addy = 0;
	if (main->map.grid[(int)(pos.y - 0.1 + mv.y)][(int)(pos.x + 0.1)] == WALL)
		addy = 0;
	if (main->map.grid[(int)(pos.y + 0.1 + mv.y)][(int)(pos.x - 0.1)] == WALL)
		addy = 0;
	if (main->map.grid[(int)(pos.y - 0.1 + mv.y)][(int)(pos.x - 0.1)] == WALL)
		addy = 0;
	if (addy == 1)
		main->player.pos.y += mv.y;
	if (addx == 1)
		main->player.pos.x += mv.x;
}

float	deg_to_rad(float angle)
{
	return (angle * M_PI / 180.0);
}

t_vect	rotate_vector(t_vect vec, float angle)
{
	t_vect	vec2;
	float	rad_angle;

	rad_angle = deg_to_rad(angle);
	vec2.x = (cos(rad_angle) * vec.x) - (sin(rad_angle) * vec.y);
	vec2.y = (sin(rad_angle) * vec.x) + (cos(rad_angle) * vec.y);
	return (vec2);
}

t_vect	normalize_vec(t_vect vec)
{
	float	a;
	float	b;
	float	c;

	a = vec.x * vec.x;
	b = vec.y * vec.y;
	c = sqrt(a + b);
	vec.x = vec.x / c;
	vec.y = vec.y / c;
	return (vec);
}

void	error_exit(char *message, t_main *main)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	game_end(main);
	exit (1);
}

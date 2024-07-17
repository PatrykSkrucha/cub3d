/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:18 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:06:01 by ncornacc      ########   odam.nl         */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:26 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 16:18:43 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stdint.h>

void	init_step_and_side_dist(t_raycast *r, t_vect pos, t_vect raydir)
{
	if (raydir.x < 0)
	{
		r->stepx = -1;
		r->sidedistx = (pos.x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - pos.x) * r->deltadistx;
	}
	if (raydir.y < 0)
	{
		r->stepy = -1;
		r->sidedisty = (pos.y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - pos.y) * r->deltadisty;
	}
}

void	init_ray(t_raycast *r, t_vect pos, t_vect raydir)
{
	r->mapx = (int)pos.x;
	r->mapy = (int)pos.y;
	if (raydir.x == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / raydir.x);
	if (raydir.y == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / raydir.y);
	init_step_and_side_dist(r, pos, raydir);
	r->hit = 0;
}

void	ray_loop(t_raycast *r, t_map map)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (r->mapx >= map.width
			|| r->mapy >= map.height
			|| r->mapx < 0 || r->mapy < 0)
			return ;
		if (map.grid[r->mapy][r->mapx] > FLOOR)
			r->hit = 1;
	}
}

t_raycast_info	cast_ray(t_vect pos, t_vect dir, t_map map)
{
	t_raycast		r;
	t_raycast_info	inf;

	init_ray(&r, pos, dir);
	ray_loop(&r, map);
	set_distance(&r);
	set_hit_position(&r, pos, dir);
	r.raydirx = dir.x;
	r.raydiry = dir.y;
	inf.dir = dir;
	inf.start = pos;
	inf.perpwalldist = r.perpwalldist;
	inf.hit_pos = r.hit_pos;
	inf.side = r.side;
	return (inf);
}

void	set_distance(t_raycast *r)
{
	if (r->side == 0 && r->hit == 1)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	else if (r->hit == 1)
		r->perpwalldist = (r->sidedisty - r->deltadisty);
	else
		r->perpwalldist = 0;
}

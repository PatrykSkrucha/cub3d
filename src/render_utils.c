/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 12:19:34 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 12:48:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    ray_loop(t_ray *r, t_map map)
{
    while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x >= map.width
			|| r->map_y >= map.height
			|| r->map_x < 0 || r->map_y < 0)
			return ;
		if (map.grid[r->map_y][r->map_x] > FLOOR)
			r->hit = 1;
	}
}

void	set_distance(t_ray *r)
{
	if (r->side == 0 && r->hit == 1)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else if (r->hit == 1)
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
	else
		r->perp_wall_dist = 0;
}

void	set_hit_spot(t_ray *r, t_vect position, t_vect direction)
{
	if (r->hit == 0)
	{
		r->hit_spot = position;
		r->hit_spot = position;
	}
	else
	{
		r->hit_spot.y = position.y + r->perp_wall_dist * direction.y;
		r->hit_spot.x = position.x + r->perp_wall_dist * direction.x;
	}
}

t_ray_data  cast_ray(t_vect position, t_vect direction, t_map map)
{
    t_ray       r;
    t_ray_data  data;

    init_ray(&r, position, direction);
    ray_loop(&r, map);
    set_distance(&r);
    set_hit_spot(&r, position, direction);
    r.ray_dir_x = direction.x;
    r.ray_dir_y = direction.y;
    data.ray_dir = direction;
    data.start_pos = position;
    data.perp_wall_dist = r.perp_wall_dist;
    data.hit_spot = r.hit_spot;
    data.side = r.side;
    return(data);
}

mlx_texture_t	*get_texture(t_ray_data *r, t_textures *textures)
{
	if (r->side == 1 && r->ray_dir.y > 0)
		return (textures->no);
	if (r->side == 0 && r->ray_dir.x > 0)
		return (textures->we);
	if (r->side == 1 && r->ray_dir.y < 0)
		return (textures->so);
	if (r->side == 0 && r->ray_dir.x < 0)
		return (textures->ea);
	return (NULL);
}

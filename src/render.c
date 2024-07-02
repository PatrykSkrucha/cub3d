/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 12:10:49 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/27 18:53:55 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_vect    get_direction(uint32_t x, t_main *main)
{
    double	camera_x;
	t_vect	ray_direction;

	camera_x = main->fov * ((float)x / main->image->width) - (main->fov / 2);
	ray_direction.x = main->player.direction.x + (main->player.plane.x) * camera_x;
	ray_direction.y = main->player.direction.y + (main->player.plane.y) * camera_x;
	return (ray_direction);
}



void    draw_rays(t_main *main)
{
    uint32_t		x;
	t_ray_data	    r;
	t_vect			direction;
	t_vect			position;

	x = 0;
	position = main->player.position;
	while (x < main->image->width)
	{
		direction = get_direction(x, main);
		r = cast_ray(position, direction, main->map);
		draw_wall(x, r, main, get_texture(&r, &main->map.assets.textures));
		x++;
	}
    
}

void    draw_F_C(t_main *main)
{
    int	x;
	int	y;

	y = 0;
	while (y < (int)main->image->height)
	{
		x = 0;
		while (x < (int)main->image->width)
		{
			if (y < (int)(main->image->height / 2 + main->player.turn_direction))
				mlx_put_pixel(main->image, x, y, main->map.assets.color_ceiling);
			else
				mlx_put_pixel(main->image, x, y, main->map.assets.color_floor);
			x++;
		}
		y++;
	}
}

void    clear(t_main *main)
{
    ft_bzero(main->image->pixels, (main->image->width * main->image->height) * 4);
}

void    render_single_frame(t_main *main)
{
    clear(main);
    draw_F_C(main);
    draw_rays(main);
}
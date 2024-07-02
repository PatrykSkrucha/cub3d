/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 13:03:52 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/27 18:37:17 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


float	get_wall_x(t_main *main, t_ray_data r)
{
    float	wall_x;

	if (r.side == 0)
		wall_x = main->player.position.y + r.perp_wall_dist * r.ray_dir.y;
	else
		wall_x = main->player.position.x + r.perp_wall_dist * r.ray_dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_y(int height, int lineheight, int counter)
{
	return (height * ((float)counter / (float)lineheight));
}

u_int32_t	get_color(mlx_texture_t *tex, int x, int y, int alpha)
{
	int	red;
	int	green;
	int	blue;
	int	i;

	i = y * tex->width + x;
	red = tex->pixels[i * tex->bytes_per_pixel];
	green = tex->pixels[i * tex->bytes_per_pixel + 1];
	blue = tex->pixels[i * tex->bytes_per_pixel + 2];
	return (parse_color(red, green, blue, alpha));
}

int get_alpha(t_ray_data *r, t_main *main)
{
    float	color_gradient;

	if (r->perp_wall_dist / main->render_distance < 1.0)
		color_gradient = 1 / cos((r->perp_wall_dist / main->render_distance)
				* (M_PI / 2));
	else
		color_gradient = 1 / cos(M_PI / 2);
	return ((int)(255 / color_gradient));
}

#include <stdio.h>

void	draw_wall(uint32_t x, t_ray_data r, t_main *main, mlx_texture_t *text)
{
	t_draw      d;
	int			c;
	int			y;

	c = 0;
	d.line_height = (main->image->width / r.perp_wall_dist) / main->fov;
	d.draw_start = (-d.line_height / 2) + ((main->image->height)
			/ 2 + (int)main->player.turn_direction);
	d.draw_end = (d.line_height / 2) + ((main->image->height) / 2) + (int)main->player.turn_direction;
	d.wall_x = get_wall_x(main, r);
	d.text_x = (double)(text->width * d.wall_x);
	y = d.draw_start;
	while (y > d.draw_end && y < (int)main->image->height)
	{
		
		if (y >= 0)
		{
			d.text_y = get_texture_y(text->height, d.line_height, c);
			mlx_put_pixel(main->image, x, y,
				get_color(text, d.text_x, d.text_y, get_alpha(&r, main)));
		}
		c++;
		y++;
	}
}
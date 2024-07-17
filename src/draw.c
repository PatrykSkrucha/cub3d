/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:55:57 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:00:45 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

float	get_wall_x(t_main *main, t_raycast_info r)
{
	float	wall_x;

	if (r.side == 0)
		wall_x = main->player.pos.y + r.perpwalldist * r.dir.y;
	else
		wall_x = main->player.pos.x + r.perpwalldist * r.dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	get_texture_y(int picture_height, int lineheight, int counter)
{
	return (picture_height * ((float)counter / (float)lineheight));
}

int	get_alpha(t_raycast_info *r, t_main *main)
{
	float	color_falloff;

	if (r->perpwalldist / main->render_distance < 1.0)
		color_falloff = 1 / cos((r->perpwalldist / main->render_distance)
				* (M_PI / 2));
	else
		color_falloff = 1 / cos(M_PI / 2);
	return ((int)(255 / color_falloff));
}

u_int32_t	parse_color(mlx_texture_t *tex, int x, int y, int alpha)
{
	int	red;
	int	green;
	int	blue;
	int	i;

	i = y * tex->width + x;
	red = tex->pixels[i * tex->bytes_per_pixel];
	green = tex->pixels[i * tex->bytes_per_pixel + 1];
	blue = tex->pixels[i * tex->bytes_per_pixel + 2];
	return (get_rgba(red, green, blue, alpha));
}


void	draw_wall(uint32_t x, t_raycast_info r,
	t_main *main, mlx_texture_t *text)
{
	t_draw			d;
	int				c;
	int				y;

	c = 0;
	d.lh = (main->image->width / r.perpwalldist) / main->fov;
	d.start = (-d.lh / 2) + ((main->image->height)
			/ 2 + (int)main->player.head_pitch);
	d.end = (d.lh / 2) + ((main->image->height) / 2) + (int)main->player.head_pitch;
	d.wallx = get_wall_x(main, r);
	d.texx = (double)(text->width * d.wallx);
	y = d.start;
	while (y < d.end && y < (int)main->image->height)
	{
		if (y >= 0)
		{
			d.texy = get_texture_y(text->height, d.lh, c);
			mlx_put_pixel(main->image, x, y,
				parse_color(text, d.texx, d.texy, get_alpha(&r, main)));
		}
		c++;
		y++;
	}
}

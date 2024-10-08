/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:48 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 16:29:05 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	draw_floor_and_ceiling(t_main *main)
{
	int	x;
	int	y;

	y = 0;
	while (y < (int)main->image->height)
	{
		x = 0;
		while (x < (int)main->image->width)
		{
			if (y < (int)(main->image->height / 2 + main->player.head_pitch))
				mlx_put_pixel(main->image, x, y, main->map.assets.col_ceiling);
			else
				mlx_put_pixel(main->image, x, y, main->map.assets.col_floor);
			x++;
		}
		y++;
	}
}

mlx_texture_t	*get_texture(t_raycast_info *r, t_texture *textures)
{
	if (r->side == 1 && r->dir.y > 0)
		return (textures->north_wall);
	if (r->side == 0 && r->dir.x > 0)
		return (textures->west_wall);
	if (r->side == 1 && r->dir.y < 0)
		return (textures->south_wall);
	if (r->side == 0 && r->dir.x < 0)
		return (textures->east_wall);
	return (NULL);
}

bool	in_image(mlx_image_t *image, uint32_t x, uint32_t y)
{
	return (x > 0 && x < image->width && y > 0 && y < image->height);
}

void	draw_line(mlx_image_t *image, t_vect cur,
				t_vect end, unsigned int color)
{
	int		dx;
	int		dy;

	dx = (int)(end.x) - (int)(cur.x);
	dy = (int)(end.y) - (int)(cur.y);
	if (abs(dx) > abs(dy))
	{
		while ((int)cur.x != (int)(end.x) && in_image(image, cur.x, cur.y))
		{
			mlx_put_pixel(image, round(cur.x), round(cur.y), color);
			cur.y += (float)dy / abs(dx);
			cur.x += (float)dx / abs(dx);
		}
	}
	else
	{
		while ((int)cur.y != (int)(end.y) && in_image(image, cur.x, cur.y))
		{
			mlx_put_pixel(image, round(cur.x), round(cur.y), color);
			cur.y += (float)dy / abs(dy);
			cur.x += (float)dx / abs(dy);
		}
	}
}

void	set_hit_position(t_raycast *r, t_vect pos, t_vect raydir)
{
	if (r->hit == 0)
	{
		r->hit_pos = pos;
		r->hit_pos = pos;
	}
	else
	{
		r->hit_pos.y = pos.y + r->perpwalldist * raydir.y;
		r->hit_pos.x = pos.x + r->perpwalldist * raydir.x;
	}
}

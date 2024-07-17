/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:55:52 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 12:58:01 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vect	get_dir(uint32_t x, t_main *cub)
{
	double	camx;
	t_vect	raydir;

	camx = cub->fov * ((float)x / cub->image->width) - (cub->fov / 2);
	raydir.x = cub->player.dir.x + (cub->player.c_plane.x) * camx;
	raydir.y = cub->player.dir.y + (cub->player.c_plane.y) * camx;
	return (raydir);
}

void	draw_with_raycasts(t_main *cub)
{
	uint32_t		x;
	t_raycast_info	r;
	t_vect			dir;
	t_vect			pos;

	x = 0;
	pos = cub->player.pos;
	while (x < cub->image->width)
	{
		dir = get_dir(x, cub);
		r = cast_ray(pos, dir, cub->map);
		draw_wall(x, r, cub, get_texture(&r, &cub->map.assets.texture));
		x++;
	}
}

void	clear_images(t_main *cub)
{
	ft_bzero(cub->image->pixels, (cub->image->width * cub->image->height) * 4);
}

void	render_single_frame(t_main *cub)
{
	clear_images(cub);
	draw_floor_and_ceiling(cub);
	draw_with_raycasts(cub);
}

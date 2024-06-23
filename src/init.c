/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 11:03:59 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 13:52:52 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static  bool    init_image(t_main *main)
{
    main->image = mlx_new_image(main->window, WIDTH, HEIGHT);
    if (!main->image)
        return (false);
    return (true);
}

void    player_orientation(t_main *main)
{
    if (main->map.grid[main->map.player_y][main->map.player_x] == PLAYER_N)
    {
        main->player.direction.x = 0;
        main->player.direction.y = -1;

    }
       if (main->map.grid[main->map.player_y][main->map.player_x] == PLAYER_E)
    {
        main->player.direction.x = 1;
        main->player.direction.y = 0;

    }
       if (main->map.grid[main->map.player_y][main->map.player_x] == PLAYER_S)
    {
        main->player.direction.x = 0;
        main->player.direction.y = 1;

    }
       if (main->map.grid[main->map.player_y][main->map.player_x] == PLAYER_W)
    {
        main->player.direction.x = -1;
        main->player.direction.y = 0;

    }
}

void    init_player(t_main *main)
{
   	player_orientation(main);
    main->player.position.x = main->map.player_x;
    main->player.position.y = main->map.player_y;
    main->map.grid[main->map.player_y][main->map.player_x] = FLOOR;
    main->player.plane = rotate_vector(main->player.direction, 90);
    main->player.move_speed = 4;
    main->player.rotation_speed = 200;
    main->player.turn_direction = 0;
}

bool    init_game(t_main *main)
{
    init_player(main);
    main->window = mlx_init(WIDTH, HEIGHT, "Cube3D", 1);
    if (main->window == NULL)
        return (error_msg("MLX init failed\n", main), false);
    if (!init_image(main))
        return (error_msg("image Init failed!\n", main), false);
    main->fov = 3.0;
    main->render_distance = 10;
    main->map.grid[main->map.player_y][main->map.player_x] = FLOOR;
    return (true);
}

void	init_step_and_side_dist(t_ray *r, t_vect position, t_vect direction)
{
	if (direction.x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (position.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - position.x) * r->delta_dist_x;
	}
	if (direction.y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (position.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - position.y) * r->delta_dist_y;
	}
}

void	init_ray(t_ray *ray, t_vect position, t_vect direction)
{
    ray->map_x = (int)position.x;
	ray->map_y = (int)position.y;
	if (direction.x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / direction.x);
	if (direction.y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / direction.y);
	init_step_and_side_dist(ray, position, direction);
	ray->hit = 0;
}
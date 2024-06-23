/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 10:33:21 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 12:27:16 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    flood_fill(t_map *map, int y, int x)
{
    bool    ret;

   	ret = true;
	if (x == 0 || y == 0 || x == map->width - 1
		|| y == map->height - 1 || map->grid[y][x] == EMPTY)
		return (false);
	map->grid[y][x] = TEMP;
	if (x > 0 && map->grid[y][x - 1] != WALL && map->grid[y][x - 1] != TEMP)
		ret = flood_fill(map, y, x - 1);
	if (ret && x < map->width && map->grid[y][x + 1] != WALL
			&& map->grid[y][x + 1] != TEMP)
		ret = flood_fill(map, y, x + 1);
	if (ret && y > 0 && map->grid[y - 1][x] != WALL
			&& map->grid[y - 1][x] != TEMP)
		ret = flood_fill(map, y - 1, x);
	if (ret && y < map->height && map->grid[y + 1][x] != WALL
			&& map->grid[y + 1][x] != TEMP)
		ret = flood_fill(map, y + 1, x);
	return (ret);
}

bool    check_map(t_main *main)
{
    t_tile  player;

    if (main->map.player_x == -1)
        return(error_msg("No Player Present!\n", main), false);
    player = main->map.grid[main->map.player_y][main->map.player_x];
    if (!flood_fill(&main->map, main->map.player_y, main->map.player_x))
        return (error_msg("No valid Path for Player!\n", main), false);
    set_tiles(&main->map);
    main->map.grid[main->map.player_y][main->map.player_x] = player;
    return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:55:14 by ncornacc          #+#    #+#             */
/*   Updated: 2024/08/21 19:18:37 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>

bool	allocate_map_tiles(t_map *map)
{
	int	i;

	i = 0;
	map->grid = ft_calloc(map->height + 1, sizeof(t_tile *));
	if (map->grid == NULL)
		return (false);
	while (i < map->height)
	{
		map->grid[i] = ft_calloc(map->width + 1, sizeof(t_tile));
		if ((map->grid)[i] == NULL)
		{
			ft_2dfree((char **)map->grid);
			return (false);
		}
		i++;
	}
	return (true);
}

t_tile	get_tile(char c)
{
	if (c == ' ')
		return (SPACE);
	else if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (NO);
	else if (c == 'E')
		return (EA);
	else if (c == 'S')
		return (SO);
	else if (c == 'W')
		return (WE);
	return (SPACE);
}

bool	get_player_pos(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == NO || map->grid[y][x] == EA
					|| map->grid[y][x] == SO || map->grid[y][x] == WE)
			{
				if (map->px != -1)
					return (false);
				map->py = y;
				map->px = x;
			}
			x++;
		}
		y++;
	}
	return (true);
}

void	set_tiles(t_map *map)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = map_start_index(map->str_map);
	while (map->str_map[i])
	{
		j = 0;
		while (map->str_map[i][j])
		{
			map->grid[y][j] = get_tile(map->str_map[i][j]);
			j++;
		}
		y++;
		i++;
	}
}

bool	setup_map(t_main *main)
{
	main->map.px = -1;
	main->map.py = -1;
	//if (!determine_map_height(&main->map))
	//	return (error_msg("Failed to determine map height\n", main), false);
	//if (!determine_map_width(&main->map))
		//return (error_msg("Failed to determine map width\n", main), false);
	if (!allocate_map_tiles(&main->map))
		return (error_msg("Map tile allocation failed\n", main), false);
	set_tiles(&main->map);
	if (!get_player_pos(&main->map))
		return (error_msg("mulitple player positions\n", main), false);
	return (true);
}

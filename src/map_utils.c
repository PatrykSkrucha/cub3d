/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:54:58 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/17 13:01:56 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>
#define EXTENSION_LENGTH 4

bool	extension_check(char *map_path)
{
	if (!map_path)
		return (false);
	if (ft_strlen(map_path) <= EXTENSION_LENGTH)
		return (false);
	if (ft_strncmp(map_path + ft_strlen(map_path)
			- EXTENSION_LENGTH, ".cub", 5))
		return (false);
	return (true);
}

bool	open_file(char *map_path, int *fd)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	read_file(int file, t_map *map)
{
	char	*line;
	char	**str_map;
	char	**temp;

	line = get_next_line(file);
	if (!line)
		return (false);
	str_map = ft_2d_add(NULL, line);
	if (!str_map)
		return (free(line), false);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		if (!line)
			break ;
		temp = str_map;
		str_map = ft_2d_add(str_map, line);
		ft_2dfree(temp);
		if (!str_map)
			return (free(line), false);
	}
	map->str_map = str_map;
	return (true);
}

bool	flood_fill_validate(t_map *map, int y, int x)
{
	bool	ret;

	ret = true;
	if (x == 0 || y == 0 || x == map->width - 1
		|| y == map->height - 1 || map->grid[y][x] == SPACE)
		return (false);
	map->grid[y][x] = TEMP;
	if (x > 0 && map->grid[y][x - 1] != WALL && map->grid[y][x - 1] != TEMP)
		ret = flood_fill_validate(map, y, x - 1);
	if (ret && x < map->width && map->grid[y][x + 1] != WALL
			&& map->grid[y][x + 1] != TEMP)
		ret = flood_fill_validate(map, y, x + 1);
	if (ret && y > 0 && map->grid[y - 1][x] != WALL
			&& map->grid[y - 1][x] != TEMP)
		ret = flood_fill_validate(map, y - 1, x);
	if (ret && y < map->height && map->grid[y + 1][x] != WALL
			&& map->grid[y + 1][x] != TEMP)
		ret = flood_fill_validate(map, y + 1, x);
	return (ret);
}

bool	validate_map(t_main *main)
{
	t_tile	p_tile;

	if (main->map.px == -1)
		return (error_msg("No Player Location\n", main), false);
	p_tile = main->map.grid[main->map.py][main->map.px];
	if (!flood_fill_validate(&main->map, main->map.py, main->map.px))
		return (error_msg("No Valid Path\n", main), false);
	set_tiles(&main->map);
	main->map.grid[main->map.py][main->map.px] = p_tile;
	return (true);
}

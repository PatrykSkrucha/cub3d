/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scanner_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 09:54:29 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 13:48:29 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    allocate_tiles(t_map *map)
{
    int i;

    i = 0;
    map->grid = ft_calloc(map->height + 1, sizeof(t_tile *));
    if (map->grid == NULL)
        return (false);
    while (i < map->height)
    {
        map->grid[i] = ft_calloc(map->width +1, sizeof(t_tile));
        if (map->grid[i] == NULL)
        {
            matrix_free((char **)map->grid);
            return (false);
        }
        i++;
    }
    return (true);
}

t_action  assign_token(t_token token)
{
    const t_action  functions[7] = {
    [NO] = parse_no,
    [SO] = parse_so,
    [WE] = parse_we,
    [EA] = parse_ea,
    [FLOOR_COLOR] = parse_floor,
    [CEILING_COLOR] = parse_ceiling,
    };

    return (functions[token]);
}

t_token    string_to_token(char *str)
{
    if (!ft_strncmp(str, "NO", 3))
		return (NO);
	if (!ft_strncmp(str, "SO", 3))
		return (SO);
	if (!ft_strncmp(str, "WE", 3))
		return (WE);
	if (!ft_strncmp(str, "EA", 3))
		return (EA);
	if (!ft_strncmp(str, "F", 2))
		return (FLOOR_COLOR);
	if (!ft_strncmp(str, "C", 2))
	    return (CEILING_COLOR);
	return (UNKNOWN);
}

bool    parse_assets(t_assets *assets, char **line)
{
    char        **matrix;
    size_t      index;
    t_action    func;
    t_token     token;

    index = 0;
    while (line[index] != NULL)
    {
        matrix = ft_split(line[index], ' ');
        if (!matrix)
            return (false);
        token = string_to_token(matrix[0]);
        if (token != UNKNOWN)
        {
            func = assign_token(token);
            if (!func(assets, matrix[1]))
                return (matrix_free(matrix), false);
        }
        matrix_free(matrix);
        index++;
    }
    return (true);
}

t_tile put_tiles(char c)
{
    if (c == ' ')
		return (EMPTY);
	else if (c == '0')
		return (FLOOR);
	else if (c == '1')
		return (WALL);
	else if (c == 'N')
		return (PLAYER_N);
	else if (c == 'E')
		return (PLAYER_E);
	else if (c == 'S')
		return (PLAYER_S);
	else if (c == 'W')
		return (PLAYER_W);
	return (EMPTY);
}


void    set_tiles(t_map *map)
{
    int i;
    int j;
    int k;

    k = 0;
    i = find_map_start(map->map);
    while (map->map[i] && check_map_str(map->map[i]))
    {
        j = 0;
        while (map->map[i][j])
        {
            map->grid[k][j] = put_tiles(map->map[i][j]);
            j++;
        }
        k++;
        i++;
    }
}

bool    player_position(t_map *map)
{
    int y;
    int x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == PLAYER_N || map->grid[y][x] == PLAYER_E || map->grid[y][x] == PLAYER_S || map->grid[y][x] == PLAYER_W)
            {
                if(map->player_x != -1)
                    return (false);
                map->player_y = y;
                map->player_x = x;
            }
            x++;
        }
        y++;
    }
    return (true);
}

bool    init_map(t_main *main)
{
    main->map.player_x = -1;
    main->map.player_y = -1;
    if (!find_map_height(&main->map))
        return(error_msg("Failed during check of map height\n", main), false);
    if (!find_map_width(&main->map))
        return(error_msg("Failed during check of map width\n", main), false);
    if (!allocate_tiles(&main->map))
        return(error_msg("Failed during allocation of map\n", main), false);
    set_tiles(&main->map);
    if (!player_position(&main->map))
        return(error_msg("Multiple Players, remove some\n", main), false);
    return (true);
}
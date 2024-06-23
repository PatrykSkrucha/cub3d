/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scanner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 09:36:19 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 09:53:19 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    find_map_width(t_map *map)
{
    int i;
    int width;
    int max_width;

    max_width = 0;
    i = find_map_start(map->map);
    while(map->map[i] && check_map_str(map->map[i]))
    {
        width = ft_strlen(map->map[i]) - 1;
        if (width > max_width)
            max_width = width;
        i++;
    }
    map->width = max_width;
    return (true);
}

bool    find_map_height(t_map *map)
{
    int i;
    int height;

    i = find_map_start(map->map);
    height = 0;
    while (map->map[i] && map->map[i][0] != '\n')
    {
        if (!check_map_str(map->map[i]))
            return (false);
        i++;
        height++;
    }
    map->height = height;
    return (true);
}

bool    check_map_char(char c)
{
   return (c == '1' || c == ' ' || c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

bool   check_map_str(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\n')
        return (false);
    while (str[i] && str[i] != '\n')
    {
        if (!check_map_char(str[i]))
            return (false);
        i++;
    }
    return (true);
} 

int		find_map_start(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        if (check_map_str(map[i]))
            break;
        i++;
    }
    return (i);
}
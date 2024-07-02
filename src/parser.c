/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 09:03:31 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/01 01:02:36 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    parser(char *file, t_main *main)
{
    int fd;

    if (!map_ext_check(file))
        return (error_msg("Invalid Map extension\n", main), false);
    if (!open_file(file, &fd))
        return (error_msg("Error while opening the file\n", main), false);
    if (!read_file(fd, &main->map))
        return (error_msg("Error while reading the file\n", main), false);
    if (!check_order(main->map.map))
        return (error_msg("Error whith the order of the file\n", main), false);
    if (!parse_assets(&(main->map.assets), main->map.map))
        return (error_msg("Error while parsing the assets\n", main), false);
    if (!init_map(main))
        return (false);
    if (!check_map(main))
        return (false);
    return (true);
}

bool    map_ext_check(char *path)
{
    if (!path)
        return (false);
    if (ft_strlen(path) <= 4)
        return (false);
    if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 5))
        return (false);
    return (true);
}

bool    open_file(char *path, int *fd)
{
    *fd = open(path, O_RDONLY);
    if (*fd < 0)
        return (false);
    return (true);
}

bool   read_file(int file, t_map *map)
{
    char    *line;
    char    **map_line;
    char    **tmp;

    line = get_next_line(file);
    if (!line)
        return (false);
    map_line = matrix_add(NULL, line);
    if(!map_line)
        return (free(line), false);
    while (line)
    {
        free(line);
        line = get_next_line(file);
        if (!line)
            break;
        tmp = map_line;
        map_line = matrix_add(map_line, line);
        matrix_free(tmp);
        if (!map_line)
            return (free(line), false);
    }
    map->map = map_line;
    return (true);
}

bool    check_order(char **map_line)
{
    size_t  index;

    index = find_map_start(map_line);
    while (map_line[index] && check_map_str(map_line[index]))
        index++;
    while (map_line[index])
    {
        if (map_line[index][0] != '\n')
            return (false);
        index++;
    }
    return (true);
}
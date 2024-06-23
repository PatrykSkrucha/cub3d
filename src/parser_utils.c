/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 10:43:11 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 13:51:09 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    parse_so(t_assets *component, char *path)
{
    int i;

    i = ft_strlen(path);
    path[i - 1]  = '\0';
    component->textures.so = mlx_load_png(path);
    if (!component->textures.so)
        return (false);
    return (true);
}

bool    parse_we(t_assets *component, char *path)
{
    int i;

    i = ft_strlen(path);
    path[i - 1]  = '\0';
    component->textures.we = mlx_load_png(path);
    if (!component->textures.we)
        return (false);
    return (true);
}

bool    parse_ea(t_assets *component, char *path)
{
    int i;

    i = ft_strlen(path);
    path[i - 1]  = '\0';
    component->textures.ea = mlx_load_png(path);
    if (!component->textures.ea)
        return (false);
    return (true);
}

bool    parse_no(t_assets *component, char *path)
{
    int i;

    i = ft_strlen(path);
    path[i - 1]  = '\0';
    component->textures.no = mlx_load_png(path);
    if (!component->textures.no)
        return (false);
    return (true);
}

uint32_t    parse_color(int r, int g, int b, int n)
{
    return (r << 24 | g << 16 | b << 8 | n);
}

bool    parse_ceiling(t_assets *component, char *path)
{
    char        **matrix;
    uint32_t    color;

    matrix = ft_split(path, ',');
    if (!matrix && matrix_len(matrix) != 3)
        return (matrix_free(matrix), false);
    color = parse_color(ft_atoi(matrix[0]), ft_atoi(matrix[1]), ft_atoi(matrix[2]), 255);
    component->color_ceiling = color;
    matrix_free(matrix);
    return (true);
}

bool    parse_floor(t_assets *component, char *path)
{
    char        **matrix;
    uint32_t    color;

    matrix = ft_split(path, ',');
    if (!matrix && matrix_len(matrix) != 3)
        return (matrix_free(matrix), false);
    color = parse_color(ft_atoi(matrix[0]), ft_atoi(matrix[1]), ft_atoi(matrix[2]), 255);
    component->color_floor = color;
    matrix_free(matrix);
    return (true);
}
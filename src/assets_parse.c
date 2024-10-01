/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:44 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/01 20:23:13 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	north_parse(t_assets *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.north_wall = mlx_load_png(path);
	if (!texture->texture.north_wall)
		return (false);
	return (true);
}

bool	south_parse(t_assets *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.south_wall = mlx_load_png(path);
	if (!texture->texture.south_wall)
		return (false);
	return (true);
}

bool	east_parse(t_assets *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.east_wall = mlx_load_png(path);
	if (!texture->texture.east_wall)
		return (false);
	return (true);
}

bool	west_parse(t_assets *texture, char *path)
{
	int	i;

	i = ft_strlen(path);
	path[i - 1] = '\0';
	texture->texture.west_wall = mlx_load_png(path);
	if (!texture->texture.west_wall)
		return (false);
	return (true);
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	ceiling_parse(t_assets *asset, char *path)
{
	char		**matrix;
	uint32_t	col;

	matrix = ft_split(path, ',');
	if (!matrix && ft_2d_arrlen(matrix) != 3)
		return (ft_2dfree(matrix), false);
	col = get_rgba(ft_atoi(matrix[0]), ft_atoi(matrix[1]), \
			ft_atoi(matrix[2]), 255);
	asset->col_ceiling = col;
	ft_2dfree(matrix);
	return (true);
}

bool	floor_parse(t_assets *asset, char *path)
{
	char		**matrix;
	uint32_t	col;

	matrix = ft_split(path, ',');
	if (!matrix && ft_2d_arrlen(matrix) != 3)
		return (ft_2dfree(matrix), false);
	col = get_rgba(ft_atoi(matrix[0]), ft_atoi(matrix[1]), \
			ft_atoi(matrix[2]), 255);
	asset->col_floor = col;
	ft_2dfree(matrix);
	return (true);
}

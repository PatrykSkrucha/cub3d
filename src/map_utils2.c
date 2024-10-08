/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:43:49 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 16:23:55 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	not_number(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	invalid_color(char *color)
{
	if (ft_atoi(color) > 255)
		return (1);
	return (0);
}

static int	comma_check(char *color)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (color[i])
	{
		if (color[i] == ',')
			counter++;
		i++;
	}
	if (counter != 2)
		return (1);
	return (0);
}

char	**get_rgb(char **args)
{
	char	**rgb;
	int		i;

	i = 0;
	if (comma_check(args[1]))
		error_exit("Error while parsing the map RGB");
	rgb = ptr_check(ft_split(args[1], ','));
	if (double_strlen(rgb) != 3)
		error_exit("Error while parsing the map rgb");
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 3 || not_number(rgb[i])
			|| invalid_color(rgb[i]))
			error_exit("Error while parsing the map rgb");
		i++;
	}
	return (rgb);
}

int	double_strlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

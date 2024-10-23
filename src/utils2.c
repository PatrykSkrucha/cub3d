/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:56:31 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/09 17:22:15 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	strlen_no_ws_end(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (!ft_isspace(str[i]))
			break ;
		i--;
	}
	return (i + 1);
}

void	*ptr_check(void *ptr)
{
	if (!ptr)
		error_exit("Malloc failure.", NULL);
	return (ptr);
}

void	double_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	error_msg(const char *str, t_main *main)
{
	(void)main;
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	game_end(main);
}

void	preinit_main(t_main *main)
{
	main->map.width = 0;
	main->map.height = 0;
	main->map.assets.ceiling = false;
	main->map.assets.floor = false;
	main->map.player = false;
	main->map.assets.texture.east_wall = NULL;
	main->map.assets.texture.north_wall = NULL;
	main->map.assets.texture.west_wall = NULL;
	main->map.assets.texture.south_wall = NULL;
	main->map.str_map = NULL;
}

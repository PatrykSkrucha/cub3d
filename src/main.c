/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:34 by ncornacc          #+#    #+#             */
/*   Updated: 2024/08/21 19:16:48 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

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
}

int	main(int argc, char *argv[])
{
	t_main	main;

	ft_bzero(&main, sizeof(t_main));
	preinit_main(&main);
	if (argc != 2)
		return (error_msg("Invalid amount of arguments [2]\n",
				&main), EXIT_FAILURE);
	if (!parser(argv[1], &main))
		return (EXIT_FAILURE);
	if (!game_init(&main))
		return (false);
	if (!game_loop(&main))
		return (false);
	game_end(&main);
	return (EXIT_SUCCESS);
}

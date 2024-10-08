/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:34 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/08 20:09:16 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

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

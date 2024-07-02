/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 07:36:57 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/07/01 01:39:29 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

void	error_msg(const char *message, t_main *main)
{
	(void)main;
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	end_program(main);
}

int	main(int argc, char **argv)
{
	t_main	main;


	ft_bzero(&main, sizeof(t_main));
	if (argc != 2)
		return(error_msg("Invalid number of arguments\n", 
				&main), 1);
	if(!parser(argv[1], &main))
		return (error_msg("Error while parsing the map\n", 
				&main), 1);
	if (!init_game(&main))
		return (error_msg("Error while initializing the game\n", 
				&main), 1);
	if (!game_loop(&main))
		return (error_msg("Error while running the game\n", 
				&main), 1);
	end_program(&main);
	return (0);
}

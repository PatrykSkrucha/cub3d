/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:53:58 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 15:56:32 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_action_pars	check_next_step(t_main *main)
{
	if (!main->map.assets.ceiling || !main->map.assets.floor 
		|| !main->map.assets.texture.north_wall 
		|| !main->map.assets.texture.east_wall 
		|| !main->map.assets.texture.south_wall
		|| !main->map.assets.texture.west_wall)
		return (PARAMS);
	return (DO_MAP);
}

t_token	which_asset(char *line)
{
	if (!ft_strncmp(line, "C", ft_strlen(line)))
		return (CEILING_COLOR);
	if (!ft_strncmp(line, "F", ft_strlen(line)))
		return (FLOOR_COLOR);
	if (!ft_strncmp(line, "NO", ft_strlen(line)))
		return (NORTH);
	if (!ft_strncmp(line, "SO", ft_strlen(line)))
		return (SOUTH);
	if (!ft_strncmp(line, "WE", ft_strlen(line)))
		return (WEST);
	if (!ft_strncmp(line, "EA", ft_strlen(line)))
		return (EAST);
	return (-1);
}

t_action_pars	look_for_action(char *line, t_main *main)
{
	t_token_pars	token;
	t_action_pars	expected_move;

	token = check_token(line);
	expected_move = check_next_step(main);
	if (token == EMPTY_LINE && expected_move == PARAMS)
		return (SKIP);
	if (token == EMPTY_LINE && expected_move == DO_MAP)
		return (SKIP);
	if (token == MAP && expected_move == DO_MAP)
		return (DO_MAP);
	if (token == MAP && expected_move == PARAMS)
		return (EXIT);
	if (token == INFO && expected_move == DO_MAP)
		return (EXIT);
	if (token == INFO && expected_move == PARAMS)
		return (PARAMS);
	if (token == ERROR)
		return (EXIT);
	return (DO_MAP);
}


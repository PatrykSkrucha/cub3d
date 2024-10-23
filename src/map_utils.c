/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:58 by ncornacc          #+#    #+#             */
/*   Updated: 2024/10/22 16:05:18 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdbool.h>

int	calc_matrix(t_main *main)
{
	t_token_pars	token;
	t_token_pars	prev_token;
	char			*line;
	int				i;
	bool			matrix_check;

	i = 0;
	matrix_check = false;
	while (1)
	{
		line = get_next_line(main->fd);
		if (!line)
			break ;
		token = check_token(line, main);
		if (matrix_check && prev_token == EMPTY_LINE && token == MAP)
			return (free(line), -1);
		if (token == MAP)
			matrix_check = width_update(main, line);
		if (token == MAP)
			i++;
		free(line);
		prev_token = token;
	}
	return (i);
}

char	*add_extra_spaces(char *line, int len)
{
	int		i;
	char	*str;

	if ((int)ft_strlen(line) == len)
		return (line);
	i = len - (int)ft_strlen(line);
	str = ptr_check(ft_strdup(line));
	free(line);
	while (i > 0)
	{
		str = ptr_check(strjoin_free(str, " "));
		i--;
	}
	return (str);
}

char	*remove_sufix_whitespace(char *str)
{
	char	*str1;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			break ;
		i--;
	}
	str1 = ptr_check(ft_substr(str, 0, i + 1));
	free(str);
	return (str1);
}

void	fill_map(t_main *main, char *line)
{
	static int	i = -1;
	char		*line_no_nl;

	line_no_nl = remove_nl(line);
	line_no_nl = remove_sufix_whitespace(line_no_nl);
	if (line_no_nl)
		line_no_nl = add_extra_spaces(line_no_nl, main->map.width);
	i++;
	if (!line)
	{
		main->map.str_map[i] = NULL;
		return ;
	}
	else
		main->map.str_map[i] = ptr_check(ft_strdup(line_no_nl));
	free(line_no_nl);
}

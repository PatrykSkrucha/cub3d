/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:46:22 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 15:46:38 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_valid_char(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) && line[i] != ' ')
			error_exit("Space is only acceptable whitespace in map.");
		if (!ft_strchr(" 01NSEA", line[i]))
		{
			printf("line: %s\n", line);
			printf("char: >%c<\n", line[i]);
			error_exit("Error while parsing the map wrong char map.");
		}
		i++;
	}
	return (1);
}

static int	check_line_info(char *line)
{
	char	**arr;
	char	*cpy_str;

	cpy_str = ptr_check(ft_strdup(line));
	arr = ft_split(cpy_str, ' ');
	free(cpy_str);
	if (!ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	if (!ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		return (double_free(arr), 1);
	double_free(arr);
	return (0);
}

t_token_pars	check_token(char *line)
{
	char	*str;
	char	*str_trim;

	str_trim = ft_strtrim(line, " ");
	str = remove_nl(str_trim);
	free(str_trim);
	if (!str)
		return (free(str), EMPTY_LINE);
	if (check_line_info(str))
		return (free(str), INFO);
	if (check_valid_char(str))
		return (free(str), MAP);
	return (free(str), ERROR);
}
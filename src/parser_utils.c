/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:33:32 by pskrucha          #+#    #+#             */
/*   Updated: 2024/10/08 16:34:01 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#define EXTENSION_LENGTH 4

char	*remove_nl(char *line)
{
	char	*str;
	int		i;

	if (!line)
		return (NULL);
	if (!ft_strrchr(line, '\n'))
		return (ptr_check(ft_strdup(line)));
	i = ft_strlen(line);
	if ((i == 1 && line[0] == '\n') || i == 0)
		return (NULL);
	str = ptr_check(ft_calloc(i, sizeof(char)));
	ft_strlcpy(str, line, i);
	return (str);
}

char	*strjoin_free(char *to_free, char *str)
{
	char	*new_str;

	new_str = ptr_check(ft_strjoin(to_free, str));
	if (to_free)
		free(to_free);
	return (new_str);
}

bool	width_update(t_main *main, char *line)
{
	if (main->map.width < strlen_no_ws_end(line))
		main->map.width = strlen_no_ws_end(line);
	return (true);
}

bool	extension_check(char *map_path)
{
	if (!map_path)
		return (false);
	if (ft_strlen(map_path) <= EXTENSION_LENGTH)
		return (false);
	if (ft_strncmp(map_path + ft_strlen(map_path)
			- EXTENSION_LENGTH, ".cub", 5))
		return (false);
	return (true);
}

bool	open_file(char *path, t_main *main)
{
	main->fd = open(path, O_RDONLY);
	if (main->fd < 0)
		return (false);
	return (true);
}

#include "../inc/cub3d.h"

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
	str = ptr_check(ft_calloc(i - 1, sizeof(char)));
	ft_strlcpy(str, line, i);
	return (str);
}

int	open_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		error_exit("Can't access the map");
	}
	return (fd);
}

void	check_rows(char **map)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	while (map[i])
	{
		str = strtrim_space_row(map[i]);
		j = 0;
		while (str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the left side.");
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Row open on the right side.");
			j++;
		}
		free(str);
		i++;
	}
}

void	check_columns(int height, char **map)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (map[0][i])
	{
		str = strtrim_space_col(map, i, height);
		j = 0;
		while (str != NULL && str[j])
		{
			while (str[j] && str[j] == ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on top");
			while (str[j + 1] && str[j + 1] != ' ')
				j++;
			if (str[j] != '1')
				error_exit("Column open on bottom");
			j++;
		}
		if (str)
			free(str);
		i++;
	}
}

void	check_borders(char **map, int height)
{
	check_rows(map);
	check_columns(height, map);
}

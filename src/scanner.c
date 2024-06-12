#include "../inc/cub3d.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			printf("here return char: >>%c<<", line[i]);
			return (0);
		}
		i++;
	}
	printf("empty line\n");
	return (1);
}

//NO, SO, WE, EA, F, C

int check_line_info(char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
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
	return (0);
}

int	check_for_matrix(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEA", line[i]))
		{
			printf("char which doesnt fit here: >>%c<<\n", line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*remove_nl(char *line)
{
	char	*str;
	int		i;

	if (!ft_strrchr(line, '\n'))
		return (ft_strdup(line));
	i = ft_strlen(line);
	if ((i == 1  && line[0] == '\n') || i == 0) //if there's only a new line or empty string
		return (NULL);
	str = ft_calloc(i - 1, sizeof(char));
	if (!str)
		error_exit("Malloc failure");
	ft_strlcpy(str, line, i);
	return (str);
}

static t_token	check_token (char *line)
{
	char	*str;

	line = ft_strtrim(line, " ");
	str = remove_nl(line);
	if (!str)
	{
		printf("empty line\n");
		return (free(str), EMPTY_LINE);
	}
	if (check_line_info(str))
	{
		printf("info\n");
		return (free(str), INFO);
	}
	if (check_for_matrix(str))
	{
		printf("matrix\n");
		return (free(str), MATRIX);
	}
	printf("\n\n\n\n>>>error<<<\n\n\n\n");
	return (free(str), ERROR);
}

void scan_map(char **argv, t_main	*main)
{
	char		*line;
	int			fd;
	t_token		token;
	// t_action	action;

	(void)token;
	fd = open(argv[0], O_RDONLY);
	// action = PARAMS;
	if (fd == -1)
	{
		close(fd);
		error_exit("Can't access the map");
	}
	(void)main;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// line = ft_strtrim(get_next_line(fd), " ");
		//check for params()
		token = check_token(line);
		//action = info_or_map(main); //this here only if token != empty line  check if we can start with scanning map
		//check if token == empty line, then action != MAP, if yes, error and exit, empty lines can be placed at the end as well
		//if done do map scanning
		//check if there's only one player on the map
		//check if map is closed 

		printf("%s", line);
		free(line);
	}
	close(fd);
}
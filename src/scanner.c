#include "../inc/cub3d.h"

void scan_map(char **argv, t_main	*main)
{
	char	*line;
	int		fd;

	fd = open(argv[0], O_RDONLY);
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
		printf("%s", line);
		free(line);
	}
	close(fd);
}
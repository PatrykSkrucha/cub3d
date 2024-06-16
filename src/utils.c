#include "../inc/cub3d.h"

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

void	double_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	*ptr_check(void *ptr)
{
	if (!ptr)
		error_exit("Malloc failure.");
	return (ptr);
}

int	double_strlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

t_main	*init_main(void)
{
	t_main	*main;

	main = ptr_check(ft_calloc(1, sizeof(t_main)));
	// main->window = ptr_check(mlx_init(WIDTH, HEIGHT, "cub3d", true));
	// main->image = ptr_check(mlx_new_image(main->window, WIDTH, HEIGHT));
	// main->floor = ft_calloc(1, sizeof(t_rgb));
	// main->ceiling = ft_calloc(1, sizeof(t_rgb));
	return (main);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	move_pointer(char *s1, int index)
{
	if (!s1[index])
		return (0);
	if (s1[index] && ft_isspace(s1[index]))
			return (1);
	return (0);
}

static int	move_pointer_col(char **s1, int x, int y)
{
	if (y < 0 || !s1[y])
		return (0);
	if (s1[y][x] && ft_isspace(s1[y][x]))
		return (1);
	return (0);
}

char	*strtrim_space_row(char *s1)
{
	char	*str;
	int		start;
	int		end;


	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
		return (s1);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (move_pointer(s1, start))
		start++;
	while (move_pointer(s1, end))
		end--;
	if (start >= end + 1)
		return (s1);
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}

char	*concat_columns(char **str, int start, int end, int x)
{
	char	*str2;
	int		i;

	i = 0;
	str2 = ptr_check(ft_calloc(sizeof(char), end - start + 2));
	while (start + i <= end)
	{
		str2[i] = str[start + i][x];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char	*strtrim_space_col(char	**str, int x, int height)
{
	char	*str1;
	int		start;
	int		end;


	start = 0;
	end = height - 1;
	while (move_pointer_col(str, x, start))
		start++;
	while (move_pointer_col(str, x, end))
		end--;
	//printf(/"??\n");
	if (start >= end + 1)
		return (NULL);
	str1 = concat_columns(str, start, end, x);
	return (str1);
}
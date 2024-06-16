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
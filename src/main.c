#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		ft_putstr_fd("Provide path to map\n", 2);
		return (1);
	}
	
	ft_putstr_fd("hello there!\n", 1);
	return (0);
}
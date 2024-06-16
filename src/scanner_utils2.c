#include "../inc/cub3d.h"

void	print_token(t_token token)
{
	const char	*type_token[] = {
		[EMPTY_LINE] = "empty line",
		[MAP] = "map",
		[INFO] = "info",
		[ERROR] = "error",
	};
	printf("token: %s\n", type_token[token]);
}

void	print_action(t_action action)
{
	const char *type_action[] = {
		[DO_MAP] = "do_map",
		[PARAMS] = "params",
		[SKIP] = "skip",
		[EXIT] = "exit",
	};
	printf("action: %s\n", type_action[action]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/22 09:25:10 by ncornacc      #+#    #+#                 */
/*   Updated: 2024/06/22 12:25:12 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	matrix_free(char **p_arr)
{
	int	i;

	i = 0;
	if (!p_arr)
		return ;
	while (p_arr[i] != NULL)
	{
		free(p_arr[i]);
		i++;
	}
	free(p_arr);
}

int	matrix_len(char **p_arr)
{
	int	i;

	i = 0;
	while (p_arr[i] != NULL)
		i++;
	return (i);
}

static char	**empty_arr(char *str)
{
	char	**new_arr;

	new_arr = malloc(2 * sizeof(char *));
	if (!new_arr)
		return (NULL);
	new_arr[0] = ft_strdup(str);
	if (!new_arr[0])
		return (free(new_arr), NULL);
	new_arr[1] = NULL;
	return (new_arr);
}

static void	free_arr(char *new_arr[], int w_index)
{
	while (w_index >= 0)
	{
		free(new_arr[w_index]);
		w_index--;
	}
	free(new_arr);
}

char	**matrix_add(char *arr[], char *str)
{
	char	**new_arr;
	int		words;
	int		w_index;

	w_index = 0;
	if (!str)
		return (arr);
	if (!arr)
		return (empty_arr(str));
	words = matrix_len(arr);
	new_arr = ft_calloc((words + 2), sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr[w_index])
	{
		new_arr[w_index] = ft_strdup(arr[w_index]);
		if (new_arr[w_index] == NULL)
			return (free_arr(new_arr, w_index - 1), NULL);
		w_index++;
	}
	new_arr[w_index] = ft_strdup(str);
	if (new_arr[w_index] == NULL)
		return (free_arr(new_arr, w_index - 1), NULL);
	return (new_arr);
}
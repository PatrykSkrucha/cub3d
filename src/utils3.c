#include "../inc/cub3d.h"

char	*strjoin_free(char *to_free, char *str)
{
	char	*new_str;

	new_str = ptr_check(ft_strjoin(to_free, str));
	if (to_free)
		free(to_free);
	return (new_str);
}

char	*add_extra_spaces(char *line, int len)
{
	int		i;
	char	*str;

	if ((int)ft_strlen(line) == len)
		return (line);
	i = len - (int)ft_strlen(line);
	str = ptr_check(ft_strdup(line));
	free(line);
	while (i > 0)
	{
		str = ptr_check(strjoin_free(str, " "));
		i--;
	}
	return (str);
}

char	*remove_sufix_whitespace(char *str)
{
	char	*str1;
	int		i;

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			break ;
		i--;
	}
	str1 = ptr_check(ft_substr(str, 0, i + 1));
	free(str);
	return (str1);
}

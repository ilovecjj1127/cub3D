/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_helpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 17:49:26 by jcaro         #+#    #+#                 */
/*   Updated: 2024/03/04 18:01:47 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*no_new_line(char *with_new_line)
{
	char	*line;

	if (with_new_line[ft_strlen(with_new_line) - 1] != '\n')
		return (with_new_line);
	line = (char *)malloc(sizeof(char) * (ft_strlen(with_new_line)));
	if (!line)
	{
		free(with_new_line);
		return (NULL);
	}
	ft_strlcpy(line, with_new_line, ft_strlen(with_new_line));
	free(with_new_line);
	return (line);
}

int	str_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

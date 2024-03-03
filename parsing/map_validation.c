/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:08:28 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/03 18:31:49 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' )
		return (1);
	if (is_direction(c))
		return (2);
	return (0);
}

int	is_valid_line(char *line)
{
	int	valid;
	int	direction;

	valid = 0;
	direction = 0;
	while (*line)
	{
		valid = is_valid_char(*line);
		if (!valid)
		{
			printf("Error\nThe map has invalid characters\n");
			return (0);
		}
		if (valid == 2)
		{
			if (direction == 1)
				return (0);
			direction = 1;
		}
		line++;
	}
	if (direction == 1)
		return (2);
	return (1);
}

int	valid_chars(char **map)
{
	int	direction;
	int	valid_line;

	direction = 0;
	while (*map)
	{
		valid_line = is_valid_line(*map);
		if (!valid_line)
			return (0);
		if (valid_line == 2)
		{
			if (direction == 1)
			{
				printf("Error\nThe character start position is duplicated\n");
				return (0);
			}
			direction = 1;
		}
		map++;
	}
	if (direction == 0)
		printf("Error\nThe character start position is missing\n");
	return (direction);
}

static int	pos_is_surrounded(t_map *map_data, size_t row, size_t col)
{
	char	**map;
	size_t	i;
	size_t	j;

	map = map_data->map;
	if (row == 0 || row == map_data->height - 1)
		return (0);
	if (col == 0 || col == ft_strlen(map[row]) - 1)
		return (0);
	i = row - 1;
	while (i <= row + 1)
	{
		j = col - 1;
		if (i != row && j != col)
		{
			if (map[i][j] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_surrounded(t_map *map_data)
{
	size_t	row;
	size_t	col;
	char	**map;

	map = map_data->map;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == '0' || is_direction(map[row][col]))
			{
				if (!pos_is_surrounded(map_data, row, col))
				{
					printf("Error\nThe map is not surrounded by walls\n");
					return (0);
				}
			}
			col++;
		}
		row++;
	}
	return (1);
}

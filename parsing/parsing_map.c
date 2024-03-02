/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:58:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/02 20:46:18 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	get_height(int fd)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		height++;
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	return (height);
}

int	read_map(int fd, t_map *map_data)
{
	char	*line;
	char	**map;
	int		i;

	map = (char **)malloc((map_data->height + 1) * sizeof(char));
	if (!map)
		return (0);
	line = get_next_line(fd, 0);
	i = 0;
	while (line)
	{
		line = no_new_line(line);
		if (!line)
		{
			get_next_line(fd, 1);
			return (0);
		}
		map[i] = line;
		i++;
		line = get_next_line(fd, 0);
	}
	map[i] = NULL;
	map_data->map = map;
	return (1);
}

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

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
			return (0);
		if (valid == 2)
		{
			if (direction == 1)
				return (0);
			direction = 1;
		}
		line++;
	}
	if (direction == 2)
		return (2);
	return(1);
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
				return (0);
			direction = 1;
		}
		map++;
	}
	return (direction);
}

int	is_surrounded_aux(char **map, int row, int col)
{
	int	i;
	int	j;

	i = row - 1;
	while (i <= row + 1)
	{
		j = col - 1;
		if (i != row && j != col)
		{
			if (map[i][j] != '1')
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
				if (row == 0 || row == map_data->height - 1 || col == 0 || col == ft_strlen(map[row]) - 1)
					return (0);
				if (!is_surrounded_aux(map, row, col))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (0);
}

void	free_words(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

int	parse_map(int fd, char *file, t_map *map_data)
{
	map_data->height = get_height(fd);
	close(fd);
	fd = open(file, O_RDONLY, 0644);
	if (!fd)
		return (0);
	if (!read_map(fd, map_data))
	{
		close(fd);
		return(0);	
	}
	if (!valid_chars(map_data->map) || !is_surrounded(map_data))
	{
		close(fd);
		//free_words(map_data->map);
		return (0);
	}
	return (1);
}

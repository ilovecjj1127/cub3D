/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:58:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/03 18:32:20 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	get_height(int fd)
{
	char	*line;
	int		height;

	height = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	return (height);
}

static int	save_map(int fd, t_map *map_data)
{
	char	*line;
	char	**map;
	int		i;

	map = (char **)malloc((map_data->height + 1) * sizeof(char *));
	if (!map)
		return (printf("Error\nMalloc\n"), 0);
	line = read_first_line(fd);
	i = 0;
	while (line)
	{
		line = no_new_line(line);
		if (!line || ft_strlen(line) == 0)
			return (handle_line_error(fd, line, map, i));
		map[i] = line;
		i++;
		line = get_next_line(fd, 0);
	}
	map[i] = NULL;
	map_data->map = map;
	return (1);
}

static void	set_map_data(t_map *map_data)
{
	char	**map;
	int		row;
	int		col;

	map = map_data->map;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (is_direction(map[row][col]))
			{
				map_data->start_x = col;
				map_data->start_y = row;
				map_data->direction = map[row][col];
				return ;
			}
			col++;
		}
		row++;
	}
	return ;
}

int	parse_map(int fd, char *file, t_map *map_data, int lines_read)
{
	map_data->height = get_height(fd);
	close(fd);
	if (!go_to_map_start(file, lines_read))
		return (0);
	if (!save_map(fd, map_data))
		return (0);
	if (!valid_chars(map_data->map) || !is_surrounded(map_data))
	{
		free_array(map_data->map);
		return (0);
	}
	set_map_data(map_data);
	close(fd);
	return (1);
}

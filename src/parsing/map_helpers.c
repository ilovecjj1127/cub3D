/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/03 18:12:08 by jcaro         #+#    #+#                 */
/*   Updated: 2024/03/04 18:01:40 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

char	*read_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	return (line);
}

int	handle_line_error(int fd, char *line, char **map, int i)
{
	if (line)
	{
		free(line);
		printf("Error\nThe map has empty lines\n");
	}
	map[i] = NULL;
	free_array(map);
	get_next_line(fd, 1);
	return (0);
}

int	go_to_map_start(char *file, int lines_read)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY, 0644);
	if (!fd)
	{
		printf("Error\nCould not open '%s'", file);
		return (0);
	}
	while (lines_read)
	{
		line = get_next_line(fd, 0);
		free(line);
		lines_read--;
	}
	return (1);
}

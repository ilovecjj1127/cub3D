/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/24 11:55:56 by jcaro         #+#    #+#                 */
/*   Updated: 2024/03/11 11:50:56 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	save_texture(char **element, t_textures *textures)
{
	if (ft_strlen(element[0]) == 2)
	{
		if (ft_strncmp("NO", element[0], 2) == 0)
			textures->north = element[1];
		else if (ft_strncmp("SO", element[0], 2) == 0)
			textures->south = element[1];
		else if (ft_strncmp("EA", element[0], 2) == 0)
			textures->east = element[1];
		else if (ft_strncmp("WE", element[0], 2) == 0)
			textures->west = element[1];
	}
	else if (ft_strlen(element[0]) == 1)
	{
		if (ft_strncmp("F", element[0], 1) == 0)
			textures->floor = element[1];
		else if (ft_strncmp("C", element[0], 1) == 0)
			textures->ceiling = element[1];
	}
	free(element[0]);
	free(element);
}

static int	check_element_count(char **split)
{
	if (array_size(split) == 2)
	{
		if (ft_strlen(split[0]) < 1 || \
			(ft_strncmp("NO", split[0], 3) && ft_strncmp("SO", split[0], 3) \
			&& ft_strncmp("EA", split[0], 3) && ft_strncmp("WE", split[0], 3) \
			&& ft_strncmp("F", split[0], 2) && ft_strncmp("C", split[0], 2)))
		{
			free_array(split);
			return (printf("Error\nWrong format\n"), 0);
		}
	}
	else
	{
		free_array(split);
		return (printf("Error\nWrong format\n"), 0);
	}
	return (1);
}

static char	**get_element(char *line, t_textures *textures)
{
	char	**split;

	if (!valid_spaces(line))
		return (NULL);
	split = ft_split(line, ' ');
	if (split == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	if (!check_element_count(split))
		return (NULL);
	if (check_duplicate(split, textures))
		return (free_array(split), NULL);
	if (ft_strlen(split[0]) == 2 && !is_valid_path(split[1]))
		return (free_array(split), NULL);
	if (ft_strlen(split[0]) == 1 && !is_valid_color(split[1]))
		return (free_array(split), NULL);
	return (split);
}

int	parse_textures(int fd, t_textures *textures)
{
	char	*line;
	char	**element;
	int		lines_read;

	init_textures(textures);
	line = get_next_line(fd, 0);
	lines_read = 0;
	while (!all_textures_saved(textures) && line)
	{
		if (*line != '\n')
		{
			line = no_new_line(line);
			element = get_element(line, textures);
			if (!element)
				return (handle_exit(fd, line, textures));
			save_texture(element, textures);
		}
		lines_read++;
		free(line);
		if (!all_textures_saved(textures))
			line = get_next_line(fd, 0);
	}
	if (!lines_read)
		printf("Error\nEmpty file\n");
	return (lines_read);
}

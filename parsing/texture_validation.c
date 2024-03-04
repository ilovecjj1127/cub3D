/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:55:44 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/03 18:39:08 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	valid_spaces(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] >= 9 && line[i] <= 13)
		{
			printf("Error\nInvalid spaces\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("Error\nCould not open '%s'\n", path);
		return (0);
	}
	close(fd);
	return (1);
}

int	color_in_range(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (!str_is_number(colors[i]))
			return (0);
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_color(char *color)
{
	char	**colors;
	int		valid;

	valid = 0;
	colors = ft_split(color, ',');
	if (!colors)
	{
		printf("Error\nMalloc\n");
		return (0);
	}
	if (ft_count(color, ',') == 2)
	{
		if (array_size(colors) == 3 && color_in_range(colors))
			valid = 1;
	}
	else
		printf("Error\nWrong color format\n");
	free_array(colors);
	return (valid);
}

int	check_duplicate(char **data, t_textures *textures)
{
	int	duplicated;

	duplicated = 0;
	if (ft_strncmp("NO", data[0], 2) == 0 && textures->north != NULL)
		duplicated = 1;
	else if (ft_strncmp("SO", data[0], 2) == 0 && textures->south != NULL)
		duplicated = 1;
	else if (ft_strncmp("EA", data[0], 2) == 0 && textures->east != NULL)
		duplicated = 1;
	else if (ft_strncmp("WE", data[0], 2) == 0 && textures->west != NULL)
		duplicated = 1;
	else if (ft_strncmp("F", data[0], 1) == 0 && textures->floor != NULL)
		duplicated = 1;
	else if (ft_strncmp("C", data[0], 1) == 0 && textures->ceiling != NULL)
		duplicated = 1;
	if (duplicated)
		printf("Error\nThe texture or color is duplicated\n");
	return (duplicated);
}

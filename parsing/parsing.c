/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:55:56 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/24 19:50:34 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	is_valid(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] >= 9 && line[i] <= 13)
		{
			free(line);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
}

int	is_valid_path(char *path)
{
	return (path != NULL);
}

int	is_valid_color(char *color)
{
	return (color != NULL);
}

int	check_and_save(char **texture_data, t_textures *textures)
{
	if (array_size(texture_data) != 2)
		return (0);
	if (ft_strlen(texture_data[0]) == 2 && is_valid_path(texture_data[1]))
	{
		if (ft_strncmp("NO", texture_data[0], 2) == 0 && textures->north == NULL)
			textures->north = texture_data[1];
		else if (ft_strncmp("SO", texture_data[0], 2) == 0 && textures->south == NULL)
			textures->south = texture_data[1];
		else if (ft_strncmp("EA", texture_data[0], 2) == 0 && textures->east == NULL)
			textures->east = texture_data[1];
		else if (ft_strncmp("WE", texture_data[0], 2) == 0 && textures->west == NULL)
			textures->west = texture_data[1];
	}
	else if (ft_strlen(texture_data[0]) == 1 && is_valid_color(texture_data[1]))
	{
		if (ft_strncmp("F", texture_data[0], 1) == 0 && textures->floor == NULL)
			textures->floor = texture_data[1];
		else if (ft_strncmp("C", texture_data[0], 1) == 0 && textures->ceiling == NULL)
			textures->ceiling = texture_data[1];
	}
	else
		return (0);
	return (1);
}

int	save_texture(char *line, t_textures *textures)
{
	char	**split_line;

	if (!is_valid(line))
		return (0);
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
	{
		free(line);
		return (0);
	}
	if (!check_and_save(split_line, textures))
	{
		free_array(split_line);
		return (0);
	}
	printf("%d\n", array_size(split_line));
	free(split_line[0]);
	free(split_line);
	return (1);
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

void	free_texture(t_textures *textures)
{
	if (textures->north != NULL)
		free(textures->north);
	if (textures->south != NULL)
		free(textures->south);
	if (textures->west != NULL)
		free(textures->west);
	if (textures->east != NULL)
		free(textures->east);
	if (textures->floor != NULL)
		free(textures->floor);
	if (textures->ceiling != NULL)
		free(textures->ceiling);
}

int	read_textures(char *file, t_textures *textures)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	init_textures(textures);
	line = get_next_line(fd, 0);
	while (line)
	{
		if (ft_strlen(line) != 1 && *line != '\n')
		{
			line = no_new_line(line);
			if (!save_texture(line, textures))
			{
				free_texture(textures);
				get_next_line(fd, 1);
				close(fd);
				return (0);
			}
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	close(fd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:55:56 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/02 20:40:25 by jcaro            ###   ########.fr       */
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
	{
		printf("Error\nInvalid spaces\n");
		return (0);
	}
	i = 0;
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
	int	fd;

	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("Error\nCould not open '%s'\n", path);
		return (0);
	}
	close(fd);
	return(1);
}

int	str_is_number(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (0);
		i++;
	}
	return (1);
}

int	color_in_range(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (!str_is_number(colors[i]) || ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
			return (0);
		i++;
	}
	return (1);
}
int	appearance_count(char *str, char c)
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

int	is_valid_color(char *color)
{
	char	**colors;

	colors = ft_split(color, ',');
	if (!colors)
	{
		perror("Error\n");
		return (0);
	}
	if (appearance_count(color, ',') == 2 && array_size(colors) == 3 && color_in_range(colors))
	{
		free_array(colors);
		return (1);
	}
	else
	{
		printf("Error\nWrong color format\n");
		free_array(colors);
		return (0);
	}
}

int	check_duplicate(char **texture_data, t_textures *textures)
{
	int	duplicated;

	duplicated = 0;
	if (ft_strncmp("NO", texture_data[0], 2) == 0 && textures->north != NULL)
		duplicated = 1;
	else if (ft_strncmp("SO", texture_data[0], 2) == 0 && textures->south != NULL)
		duplicated = 1;
	else if (ft_strncmp("EA", texture_data[0], 2) == 0 && textures->east != NULL)
		duplicated = 1;
	else if (ft_strncmp("WE", texture_data[0], 2) == 0 && textures->west != NULL)
		duplicated = 1;
	else if (ft_strncmp("F", texture_data[0], 1) == 0 && textures->floor != NULL)
		duplicated = 1;
	else if (ft_strncmp("C", texture_data[0], 1) == 0 && textures->ceiling != NULL)
		duplicated = 1;
	if (duplicated)
		printf("Error\nThe texture or color is duplicated\n");
	return (duplicated);
}

int	check_and_save(char **texture_data, t_textures *textures)
{
	if (array_size(texture_data) != 2 && ft_strlen(texture_data[0]) != 1 && ft_strlen(texture_data[0]) != 2)
		return (printf("Error\nWrong format\n"), 0);
	if (check_duplicate(texture_data, textures))
		return (0);
	if (ft_strlen(texture_data[0]) == 2 && is_valid_path(texture_data[1]))
	{
		if (ft_strncmp("NO", texture_data[0], 2) == 0)
			textures->north = texture_data[1];
		else if (ft_strncmp("SO", texture_data[0], 2) == 0)
			textures->south = texture_data[1];
		else if (ft_strncmp("EA", texture_data[0], 2) == 0)
			textures->east = texture_data[1];
		else if (ft_strncmp("WE", texture_data[0], 2) == 0)
			textures->west = texture_data[1];
		return (1);
	}
	else if (ft_strlen(texture_data[0]) == 1 && is_valid_color(texture_data[1]))
	{
		if (ft_strncmp("F", texture_data[0], 1) == 0)
			textures->floor = texture_data[1];
		else if (ft_strncmp("C", texture_data[0], 1) == 0)
			textures->ceiling = texture_data[1];
		return (1);
	}
	return (0);
}

int	save_texture(char *line, t_textures *textures)
{
	char	**split_line;

	if (!is_valid(line))
		return (0);
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
	{
		perror("Error\n");
		return (0);
	}
	if (!check_and_save(split_line, textures))
	{
		free_array(split_line);
		return (0);
	}
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

int	read_textures(int fd, t_textures *textures)
{
	char		*line;

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
				if (line)
					free(line);
				return (0);
			}
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	return(1);
}

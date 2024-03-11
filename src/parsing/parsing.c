/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:33:04 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/11 19:43:49 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_file_extension(char *file)
{
	char	*extension;

	if (ft_strlen(file) < 5)
		return (0);
	extension = file + (ft_strlen(file) - 4);
	return (ft_strncmp(extension, ".cub", 5) == 0);
}

int	parse_file(char *file, t_map *map_data, t_textures *textures)
{
	int	fd;
	int	lines_read;

	if (!check_file_extension(file))
	{
		printf("Error\nFile extension should be '.cub'\n");
		return (0);
	}
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("Error\nCould not open '%s'\n", file);
		return (0);
	}
	lines_read = parse_textures(fd, textures);
	if (!lines_read)
		return (0);
	if (!parse_map(fd, file, map_data, lines_read))
	{
		free_texture(textures);
		return (0);
	}
	return (1);
}

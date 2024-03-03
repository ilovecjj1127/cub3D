/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:04:52 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/03 18:37:37 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
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

int	all_textures_saved(t_textures *textures)
{
	if (textures->north == NULL)
		return (0);
	if (textures->south == NULL)
		return (0);
	if (textures->west == NULL)
		return (0);
	if (textures->east == NULL)
		return (0);
	if (textures->floor == NULL)
		return (0);
	if (textures->ceiling == NULL)
		return (0);
	return (1);
}

int	handle_exit(int fd, char *line, t_textures *textures)
{
	free_texture(textures);
	get_next_line(fd, 1);
	if (line)
		free(line);
	close(fd);
	return (0);
}

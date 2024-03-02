/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:36:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/02 19:19:47 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

#define PARSING_H

# include "libft.h"

typedef struct s_map
{
	char		**map;
	int			width;
	size_t		height;
	int			start_x;
	int			start_y;
	char		direction;
}	t_map;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
}	t_textures;

int		read_textures(int fd, t_textures *textures);
char	*no_new_line(char *with_new_line);
void	free_array(char **arr);
int		parse_map(int fd, char *file, t_map *map_data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:36:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/24 17:20:21 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

#define PARSING_H

# include "libft.h"

typedef struct s_map
{
	char		**map2d;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
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

int	read_textures(char *file, t_textures *textures);
void	free_texture(t_textures *textures);

#endif
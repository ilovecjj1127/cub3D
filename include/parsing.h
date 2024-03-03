/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:36:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/03/03 18:43:32 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "libft.h"

typedef struct s_map
{
	char		**map;
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

void	free_array(char **arr);
int		array_size(char **arr);
int		ft_count(char *str, char c);
char	*no_new_line(char *with_new_line);
int		str_is_number(char *str);

int		valid_spaces(char *line);
int		is_valid_path(char *path);
int		color_in_range(char **colors);
int		is_valid_color(char *color);
int		check_duplicate(char **data, t_textures *textures);

void	init_textures(t_textures *textures);
void	free_texture(t_textures *textures);
int		all_textures_saved(t_textures *textures);
int		handle_exit(int fd, char *line, t_textures *textures);

int		is_valid_char(char c);
int		valid_chars(char **map);
int		is_surrounded(t_map *map_data);

int		is_direction(char c);
char	*read_first_line(int fd);
int		handle_line_error(int fd, char *line, char **map, int i);
int		go_to_map_start(char *file, int lines_read);

int		parse_file(char *file, t_map *map_data, t_textures *textures);
int		parse_textures(int fd, t_textures *textures);
int		parse_map(int fd, char *file, t_map *map_data, int lines_read);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 17:03:53 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/06 11:14:28 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <MLX42/MLX42.h>
# include <libft.h>

# define WIDTH 1920
# define HEIGHT 1080
# define TILE 64

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*floor;
	char			*ceiling;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	uint32_t		color_c;
	uint32_t		color_f;
}	t_textures;

typedef struct s_map
{
	char		**map;
	size_t		height;
	int			start_x;
	int			start_y;
	char		direction;
}	t_map;

typedef struct s_player
{
	double		ply_x;
	double		ply_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		speed_m;
	double		speed_r;
}	t_player;

typedef struct s_ray
{
	double		cam_x;
	double		raydir_x;
	double		raydir_y;
	double		sidedt_x;
	double		sidedt_y;
	double		deltadt_x;
	double		deltadt_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		wall_dist;
	int			line_h;
	double		draw_start;
	double		draw_end;
	int			tex_x;
	mlx_texture_t	*wall_tex;
}	t_ray;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*ply;
	t_textures	*tex;
	t_map		*map;
	t_ray		*ray;
}	t_cub;

/* init */
t_cub	*init_cub(char *file);
void	game_loop(void *param);
void	init_player(t_cub *cub);
void	load_textures(t_cub *cub);
void	free_cub(t_cub *cub, int ex, char *msg);
uint32_t	convert_color(char *str);

/* raycasting */
void	cast_ray(t_cub *cub);
void	init_ray(t_ray *ray, t_player *ply, int x);
void	init_step(t_ray *ray, t_player *ply);
void	perform_dda(t_cub *cub, t_ray *ray);

/* render */
void		calculate_wall(t_cub *cub, t_ray *ray);
void		render_wall(t_cub *cub, t_ray *ray, int x);
uint32_t	get_color(t_ray *ray, int x, int y);

/* move and rotate */
void	move(t_cub *cub);
void	move_forward(t_player *ply, char **map);
void	move_backward(t_player *ply, char **map);
void	move_left(t_player *ply, char **map);
void	move_right(t_player *ply, char **map);
void	rotate_left(t_player *ply);
void	rotate_right(t_player *ply);

/* parsing */
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
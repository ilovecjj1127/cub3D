/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessie <jessie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:03:53 by jiajchen          #+#    #+#             */
/*   Updated: 2024/02/29 17:50:44 by jessie           ###   ########.fr       */
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
# define HEIGHT 1082
# define TILE 30

typedef struct s_texture
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
	int			ceil;
	int			floor;
}	t_texture;

typedef struct s_map
{
	char		**map2d;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
}	t_map;

typedef struct s_player
{
	double		ply_x;
	double		ply_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		speed;
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
	double		tex_x;
	mlx_image_t	*wall_tex;
}	t_ray;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*ply;
	t_texture	*tex;
	t_map		*map;
	t_ray		*ray;
}	t_cub;

/* raycasting */
void	cast_ray(t_cub *cub);

/* render */
void	calculate_wall(t_cub *cub, t_ray *ray, int x);
void	render_wall(t_cub *cub, t_ray *ray, int x);
int		get_color(t_ray *ray, int y);

#endif
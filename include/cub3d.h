/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jiajchen <jiajchen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/17 17:03:53 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/02/19 16:28:10 by jiajchen      ########   odam.nl         */
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
	char		**map;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
}	t_map;

typedef struct s_player
{
	int			p_x;
	int			p_y;
}	t_player;

typedef struct s_ray
{
	/* data */
}	t_ray;


typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*ply;
	t_texture	*tex;
}	t_cub;

#endif
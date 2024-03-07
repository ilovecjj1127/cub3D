/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 12:12:11 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/03/07 10:40:43 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_forward(t_player *ply, char **map)
{
	if (map[(int)(ply->ply_x + ply->dir_x * ply->speed_m)] \
	[(int)ply->ply_y] != '1')
		ply->ply_x += ply->dir_x * ply->speed_m;
	if (map[(int)ply->ply_x][(int)(ply->ply_y + ply->dir_y \
	* ply->speed_m)] != '1')
		ply->ply_y += ply->dir_y * ply->speed_m;
}

void	move_backward(t_player *ply, char **map)
{
	if (map[(int)(ply->ply_x - ply->dir_x \
	* ply->speed_m)][(int)ply->ply_y] != '1')
		ply->ply_x -= ply->dir_x * ply->speed_m;
	if (map[(int)ply->ply_x][(int)(ply->ply_y - ply->dir_y \
	* ply->speed_m)] != '1')
		ply->ply_y -= ply->dir_y * ply->speed_m;
}

void	move_left(t_player *ply, char **map)
{
	if (map[(int)(ply->ply_x - ply->plane_x \
	* ply->speed_m)][(int)ply->ply_y] != '1')
		ply->ply_x -= ply->plane_x * ply->speed_m;
	if (map[(int)ply->ply_x][(int)(ply->ply_y - ply->plane_y \
	* ply->speed_m)] != '1')
		ply->ply_y -= ply->plane_y * ply->speed_m;
}

void	move_right(t_player *ply, char **map)
{
	if (map[(int)(ply->ply_x + ply->plane_x \
	* ply->speed_m)][(int)ply->ply_y] != '1')
		ply->ply_x += ply->plane_x * ply->speed_m;
	if (map[(int)ply->ply_x][(int)(ply->ply_y + ply->plane_y \
	* ply->speed_m)] != '1')
		ply->ply_y += ply->plane_y * ply->speed_m;
}

/**
 * <- and ->: look left and right in the maze (rotate)
 * WASD: move the point of view through the maze
 */
void	move(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_forward(cub->ply, cub->map->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move_backward(cub->ply, cub->map->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub->ply, cub->map->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub->ply, cub->map->map);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate_left(cub->ply);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate_right(cub->ply);
}
